#include <stdio.h>
#include "head.h"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: obx <file.obx>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("ObX: Could not open %s\n", argv[1]);
        return 1;
    }

    RunFile(file);

    fclose(file);
    return 0;
}