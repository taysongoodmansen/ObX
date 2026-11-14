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
    printf("Finished ");
    if (Error_count+Warning_count+Notice_count==0){
        printf("successfully");
    }
    else{
        printf("with");
        if (Error_count>0){
            printf(", %d Error(s)",Error_count);
        }
        if (Warning_count>0){
            printf(", %d Warning(s)",Warning_count);
        }
        if (Notice_count>0){
            printf(", %d Notice(s)",Notice_count);
        }
    }
    return 0;
}