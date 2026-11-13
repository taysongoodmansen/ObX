#include <stdio.h>
#include <string.h>
#include "head.h"

char current_path[128] = "$";
int path_idx = 0;
int current_line = 0;

int RunFile(FILE *file)
{
    char line[1024];

    create_object("$");

    while (fgets(line, sizeof(line), file) != NULL)
    {
        current_line++;
        process_single_line(line);
    }
}

