#include <stdio.h>
#include <string.h>
#include "head.h"

#define VarNameChars "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_"

#define scabkey_count 1
const char *scabkeys[scabkey_count] = {
    "ref"
};

void tmplist_print(char tokens[128][128], int token_count)
{
    printf("[");

    for (int i = 0; i < token_count; i++)
    {
        printf("\"%s\"", tokens[i]);

        if (i < token_count - 1)
        {
            printf(", ");
        }
    }

    printf("]\n");
}

int varchar(char character) {
    for (int i = 0; VarNameChars[i] != '\0'; i++)
    {
        if (character == VarNameChars[i])
            return 1;
    }

    return 0;
}

bool check_symbol_junction(char current, char previous, char token[128]) {
    if (current == '"') {
        if (varchar(previous)) {
            return false;
        }
    }
    if (current == '.') {
        int num_val = is_num(token);
        if (num_val == 2) {
            return false;
        }
    }
    if (current == '/' && previous == '/') {
        return false;
    }
    if (current == '*' && previous == '*'){
        return false;
    }
    if (current == '=' && previous == '='){
        return false;
    }
    if (current == '=' && previous == '>'){
        return false;
    }
    if (current == '=' && previous == '<'){
        return false;
    }
    if (current == '=' && previous == '!'){
        return false;
    }
    return true;
}

void process_single_line(char line[1024])
{
    printf("--\n");
    //tokenizing
    char tokens[128][128];
    int token_count = 0;
    char token[128] = "";
    bool in_quote = false;
    for (int i = 0; line[i] != '\0'; i++)
    {
        char current = line[i];

        char previous = '\0';

        if (i > 0)
        {
            previous = line[i - 1];
        }

        bool split = false;
        bool add_current = true;

        if (i > 0)
        {
            if (varchar(current))
            {
                if (!varchar(previous) && previous != '"')
                {
                    split = true;
                }
                char temp[128] = {current, '\0'};
                int num_val = is_num(temp);
                if (num_val == 2 && previous == '.') {
                    split = false;
                }
            }
            else
            {
                split = check_symbol_junction(current,previous,token);

                if (current == ' ' || current == '\n')
                {
                    add_current = false;
                }
            }
        }
        if (in_quote) {
            split = false;
            add_current = true;
        }

        if (split)
        {
            if (token[0] != '\0')
            {
                if (strcmp(token,"//")==0){
                    process_tokens(tokens, &token_count);
                    return;
                }
                if (token[0] == '_') {
                    if (strcmp(token,"_dir")==0) {
                        char temp[128] = "§";
                        strcat(temp,current_path);
                        strcpy(tokens[token_count], temp);
                        token_count++;
                    }
                }
                else {
                    strcpy(tokens[token_count], token);
                    token_count++;
                    for (int i=0; i<scabkey_count; i++) {
                        if (strcmp(scabkeys[i],token)==0) {
                            strcpy(tokens[token_count], "¤");
                            token_count++;
                        }
                    }
                }
            }

            token[0] = '\0';
        }

        if (add_current && current != '\n')
        {
            char temp[2] = {current, '\0'};
            strcat(token, temp);
        }
        if (current == '"' && previous != '\\') {
            in_quote = !in_quote;
        }
    }
    if (token[0] != '\n' && token[0] != '\0') {
        strcpy(tokens[token_count], token);
        token_count++;
    }
    process_tokens(tokens, &token_count);
    //tmplist_print(tokens,token_count);
}