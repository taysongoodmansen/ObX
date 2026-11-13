#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "head.h"
//bool

bool is_resolved_path(const char *value)
{
    return strncmp(value, "§", strlen("§")) == 0;
}
void remove_resolved_marker(const char *value, char path[128])
{
    strcpy(path, value + strlen("§"));
}

bool remove_last_path_segment(char path[512])
{
    if (strcmp(path, "$") == 0)
    {
        return false;
    }

    int bracket_depth = 0;
    int i = strlen(path) - 1;

    if (path[i] == '.')
        i--;

    for (; i >= 0; i--)
    {
        if (path[i] == '|')
            bracket_depth = 1-bracket_depth;
        else if (path[i] == '.' && bracket_depth == 0)
        {
            path[i] = '\0';
            return true;
        }
    }

    return false;
}

void resolve_path(
    const char *current_path,
    char tokens[128][128],
    int start,
    int end,
    char path[512]
)
{
    char pieces[128][128];

    for (int i = start; i <= end; i++)
    {
        strcpy(pieces[i-start+1],"");
        strcpy(pieces[i - start], tokens[i]);
    }

    path[0] = '\0';

    if (pieces[0][0] != '$')
    {
        strcpy(path, current_path);
        strcat(path, ".");
    }

    for (int i = 0; i <= end - start; i++)
    {
        if (pieces[i][0]=='^') {
            if (strcmp(pieces[i], "^") == 0)
            {
                if (strcmp(pieces[i+1], "f") == 0||is_num(pieces[i+1]))
                {
                    char temp[128] = "^";
                    strcat(temp,pieces[i+1]);
                    strcpy(pieces[i+1],temp);
                }
                else
                {
                    if (!remove_last_path_segment(path))
                    {
                        return_error("Cannot navigate above root");
                        return;
                    }
                }
            }
            else {
                if (strcmp(pieces[i],"^f")==0) {
                    //doing ^f
                    if (strlen(path) > 0 && path[strlen(path) - 2] == '|') {
                        char new_path[512] = "";
                        int bracket_depth = 1;
                        int cursor = strlen(path) - 3;
                        while (bracket_depth > 0) {
                            if (path[cursor]=='|') {
                                bracket_depth=0;
                            }
                            if (bracket_depth > 0) {
                                char temp[512] = "";
                                temp[0] = path[cursor];
                                temp[1] = '\0';
                                strcat(temp, new_path);
                                strcpy(new_path, temp);
                            }
                            cursor--;
                        }
                        strcpy(path,new_path);
                    }
                    else {
                        return_error("Cannot apply ^f to a non-function path");
                        return;
                    }
                }
                else {
                    //doing ^num
                    int count = atoi(pieces[i] + 1);

                    for (int j = 0; j < count; j++)
                    {
                        if (!remove_last_path_segment(path))
                        {
                            return_error("Cannot navigate above root");
                            return;
                        }
                    }
                }
            }
        }
        else
        {
            strcat(path, pieces[i]);
        }
    }
}

