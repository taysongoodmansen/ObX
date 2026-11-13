#include <stdio.h>
#include <string.h>

#include "head.h"

bool in(const char *target, char tokens[128][128], int token_count)
{
    for (int i = 0; i < token_count; i++)
    {
        if (strcmp(target, tokens[i]) == 0)
        {
            return true;
        }
    }

    return false;
}

void print_value(const char *value,const char *type) {
    if (strcmp(type, "list") == 0) {
        return;
    }
    if (strcmp(type, "object") == 0) {
        return;
    }
    if (strcmp(type, "pointer") == 0) {
        return;
    }
    printf("Printing: %s\n",value);
}
void show_data(const char *var_name) {
    int index = find_variable(var_name);
    if (index == -1) {
        printf("ObX: Variable not found\n");
        return;
    }
    printf("ObX: %d:%s:%s\n",index,variables[index].type,variables[index].value);
}

void process_tokens(char tokens[128][128],int *token_count) {
    //tmplist_print(tokens,*token_count);
    while (in("(",tokens,*token_count)) {
        int idx = 0;
        int left_par = -1;
        int right_par = -1;
        for (idx; left_par == -1; idx++) {
            if (strcmp(tokens[idx],"(")==0) {
                left_par = idx;
            }
        }
        int depth = 1;
        for (idx; right_par == -1 && idx < *token_count; idx++) {
            if (strcmp(tokens[idx],"(")==0) {
                depth++;
            }
            else if (strcmp(tokens[idx],")")==0) {
                depth--;
            }
            if (depth == 0) {
                right_par = idx;
            }
        }
        if (right_par == -1) {
            return_error("No matching )");
            return;
        }
        else {
            parse(tokens,token_count,left_par,right_par);
        }
    }
    if (in("print",tokens,*token_count)) {
        char *value = tokens[2];
        char *type = detect_type(value);
        print_value(value,type);
    }
    else if (in("show_data",tokens,*token_count)) {
        show_data(tokens[2]);
    }
    else if (in("dir",tokens,*token_count)) {
        char result[128][128];
        int result_count = 0;

        resolve_expression(tokens,token_count,1,*token_count - 1,result,&result_count,false,"");

        if (result_count == 1)
        {
            strcpy(current_path,result[0]);
        }
    }
    else if (in("=",tokens,*token_count)) {
        int eidx = -1;
        for (eidx = 0; eidx < *token_count; eidx++)
        {
            if (strcmp(tokens[eidx], "=") == 0)
                break;
        }

        char result[128][128];
        int result_count = 0;

        resolve_expression(tokens,token_count,0,eidx-1,result,&result_count,false,"");
        replace_tokens(tokens,token_count,0,eidx-1,result,result_count);

        resolve_expression(tokens,token_count,2,*token_count-1,result,&result_count,true,"");
        replace_tokens(tokens,token_count,2,*token_count-1,result,result_count);

        char path[128];
        strcpy(path, tokens[0]);
        if (strcmp(tokens[2],"[")) {
            char value[128];
            strcpy(value, tokens[2]);
            set_variable_value(path,value);
        }
        else {
            assign_collection(path,tokens,2,*token_count-1);
        }
    }
    else if (strcmp(tokens[0], "object") == 0) {
        char path[512];
        resolve_path(current_path,tokens,1,1,path);
        create_object(path);
    }
    //tmplist_print(tokens,*token_count);
}

