#include "Response.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* render_template(char* filename){
    FILE* file =fopen(filename, "r");

    if (file == NULL)
    {
        return NULL;
    }else{
        printf("\n%s does exist\n", filename);
    }

    //set pointer to end to get strlen
    fseek(file,0, SEEK_END);
    long file_size = ftell(file);

    //set pointer to begin
    fseek(file,0, SEEK_SET);
    char* temp = malloc(sizeof(char)*(file_size+1));
    char c;
    int i = 0;
    while ((c = fgetc(file)) != EOF)
    {
        temp[i] = c;
        i += 1;
    }
    fclose(file);
    return temp; 
}