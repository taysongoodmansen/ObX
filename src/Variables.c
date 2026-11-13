#include <stdio.h>
#include <string.h>

#include "head.h"

#define MAX_VARIABLES 128

ObXValue variables[MAX_VARIABLES];
int variable_count = 0;

//handling
bool contains(const char *target, const char *value)
{
    return strstr(value, target) != NULL;
}

int is_num(const char value[128]) {
    if (value[0] == '\0') {
        return 0;
    }
    int val = 2;
    for (int i = 0; value[i] != '\0'; i++)
    {
        char current = value[i];
        if (current == '.') {
            val = 1;
        }
        else {
            if (!(current >= '0' && current <= '9'))
            {
                return 0;
            }
        }
    }
    return val;
}

char *detect_type(const char value[128])
{
    if (contains("\"", value))
    {
        return "string";
    }
    int num_val = is_num(value);
    if (num_val == 2) {
        return "integer";
    }
    if (num_val == 1) {
        return "float";
    }
    if (strcmp(value, "True") == 0 || strcmp(value, "False") == 0) {
        return "bool";
    }
    if (strncmp(value, "§", strlen("§")) == 0) {
        return "resolved path";
    }
    if (value[0]=='[') {
        return "collection";
    }
    return "unknown";
}

int find_variable(const char *path)
{
    for (int i = 0; i < variable_count; i++)
    {
        // Ignore invalidated variables.
        if (strcmp(variables[i].type, "Null") == 0)
        {
            continue;
        }

        if (strcmp(variables[i].path, path) == 0)
        {
            return i;
        }
    }

    return -1;
}

void set_variable_value(char path[128], char value[128])
{
    char clean_value[128];
    strcpy(clean_value, value);
    if (is_resolved_path(clean_value))
    {
        memmove(
            clean_value,
            clean_value + strlen("§"),
            strlen(clean_value + strlen("§")) + 1
        );
    }
    char *type = detect_type(clean_value);
    int index = find_variable(path);
    if (index == -1)
    {
        if (strchr(path, '[') != NULL)
        {
            char current[512] = "";
            int bracket_depth = 0;
            int len = 0;
            bool in_string = false;

            for (int i = 0; path[i] != '\0'; i++)
            {
                char c = path[i];

                if (c == '"' && (i == 0 || path[i - 1] != '\\'))
                {
                    in_string = !in_string;
                }

                if (!in_string)
                {
                    if (c == '[')
                        bracket_depth++;
                    else if (c == ']')
                        bracket_depth--;
                }
                if (c == ']' && bracket_depth == 0 && !in_string)
                {
                    char parent[512];
                    strcpy(parent, current);

                    char *bracket = strrchr(parent, '[');

                    if (bracket != NULL)
                    {
                        *bracket = '\0';

                        int parent_index = find_variable(parent);
                        if (parent_index == -1) {
                            char blank[128] = "[]";
                            set_variable_value(parent,blank);
                        }
                        else {
                            char parent_type[128];
                            strcpy(parent_type,variables[parent_index].type);
                            if (strcmp(parent_type, "collection") == 0)
                            {
                                int count = variables[parent_index].object.attribute_count;

                                variables[parent_index].object.attributes[count] = variable_count;
                                variables[parent_index].object.attribute_count++;

                            }
                            else {
                                return_error("Can only index values of type collection");
                                return;
                            }
                        }
                    }
                }

                len = strlen(current);

                if (len < sizeof(current) - 1)
                {
                    current[len] = c;
                    current[len + 1] = '\0';
                }
            }
        }
        char parent[512];
        strcpy(parent,path);
        remove_last_path_segment(parent);
        int parent_index = find_variable(parent);
        if (parent_index > -1) {
            int attribute_count = variables[parent_index].object.attribute_count;

            variables[parent_index].object.attributes[attribute_count] = variable_count;
            variables[parent_index].object.attribute_count++;
        }

        ObXValue variable;
        strcpy(variable.path, path);
        strcpy(variable.value, clean_value);
        strcpy(variable.type, type);

        variables[variable_count] = variable;
        variable_count++;
    }
    else
    {
        strcpy(variables[index].value, clean_value);
        strcpy(variables[index].type, type);
    }
}

int create_object(const char *path) {
    ObXValue object;
    strcpy(object.path, path);
    strcpy(object.type, "object");
    object.object.attribute_count = 0;
    variables[variable_count] = object;
    variable_count++;
    return (variable_count - 1);
}

void assign_collection(const char *parent,char tokens[128][128],const int leftbrac,const int rightbrac) {

    int parent_index = find_variable(parent);

    if (parent_index == -1)
    {
        parent_index = create_object(parent);
        strcpy(variables[parent_index].type, "collection");
    }
    else
    {
        if (strcmp(variables[parent_index].type, "collection") != 0)
        {
            return_error("Cannot assign a collection to a non-collection value");
            return;
        }
        int attribute_count = variables[parent_index].object.attribute_count;

        for (int i = 0; i < attribute_count; i++)
        {
            int child_index = variables[parent_index].object.attributes[i];

            strcpy(variables[child_index].type, "Null");
        }

        variables[parent_index].object.attribute_count = 0;
    }
    int index_count = 0;
    int entry_start = leftbrac + 1;
    int bracket_depth = 0;

    for (int i = leftbrac + 1; i <= rightbrac; i++)
    {
        bool at_end = (i == rightbrac);
        char *cur = tokens[i];

        if (!at_end)
        {
            if (strcmp(cur, "[") == 0)
                bracket_depth++;
            else if (strcmp(cur, "]") == 0)
                bracket_depth--;
        }

        if (at_end || (strcmp(cur, ",") == 0 && bracket_depth == 0))
        {
            if (entry_start >= i)
            {
                return_error("Collection entry cannot be empty");
                return;
            }

            // Find a dictionary separator at the current level.
            int colon = -1;
            int depth = 0;

            for (int j = entry_start; j < i; j++)
            {
                if (strcmp(tokens[j], "[") == 0)
                    depth++;
                else if (strcmp(tokens[j], "]") == 0)
                    depth--;
                else if (strcmp(tokens[j], ":") == 0 && depth == 0)
                {
                    colon = j;
                    break;
                }
            }

            if (colon != -1)
            {
                // Dictionary entry: key:value
                if (colon != entry_start && colon + 1 < i)
                {
                    char key[128] = "";
                    char value[128] = "";

                    // Keys and values must each be a single resolved token for now.
                    if (colon - entry_start != 1 || i - colon != 2)
                    {
                        return_error("Dictionary keys and values must each be a single token");
                        return;
                    }

                    strcpy(key, tokens[entry_start]);
                    strcpy(value, tokens[colon + 1]);

                    char path[128];
                    snprintf(path, sizeof(path), "%s[", parent);
                    strcat(path, key);
                    strcat(path, "]");

                    set_variable_value(path, value);
                }
                else
                {
                    return_error("Dictionary entry requires a key and value");
                    return;
                }
            }
            else
            {
                // Array entry: use a numeric index.
                char path[128];
                char key[32];

                snprintf(key, sizeof(key), "%d", index_count);
                snprintf(path, sizeof(path), "%s[%s]", parent, key);

                if (strcmp(tokens[entry_start], "[") == 0)
                {
                    // Create a real nested collection.
                    create_object(path);

                    strcpy(variables[find_variable(path)].type, "collection");

                    // Recursively populate the nested collection.
                    assign_collection(
                        path,
                        tokens,
                        entry_start,
                        i - 1
                    );
                }
                else if (i - entry_start == 1)
                {
                    set_variable_value(path, tokens[entry_start]);
                }
                else
                {
                    return_error("Invalid collection entry");
                    return;
                }

                index_count++;
            }

            entry_start = i + 1;
        }
    }
}

