#include "Response.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned long getFileSize(char* fileName){
    FILE* file =fopen(fileName, "rb");

    if (file == NULL)
    {
        return 0;
    }else{
        printf("\n%s does exist\n", fileName);
    }

    //set pointer to end to get strlen
    fseek(file,0, SEEK_END);
    unsigned long file_size = ftell(file);

    //set pointer to begin
    fseek(file,0, SEEK_SET);
    fclose(file);
    return file_size;
}


char* find_type(char* filename){
    char *p = malloc(sizeof(char)*50);  // pointer to the type found
    int i;
    char buf1[100]; // used to store the extension of the file
    char buf2[100];

    strcpy(buf1, filename);

    /* find the extension: */
    for (i = 0; i<strlen(buf1); i++) {
        if ( buf1[i] == '.' ) {
            strcpy(buf2, &buf1[i]);
            break;
        }
    }
    /* find the type: */
    if ( strcmp(buf2, ".html") == 0 || strcmp (buf2, ".hml") == 0) {
        strcpy (buf2, "Content-Type: text/html\r\n");
    }

    else if ( strcmp(buf2, ".txt") == 0) {
        strcpy (buf2, "Content-Type: text/plain\r\n");
    }

    else if ( strcmp(buf2, ".jpg") == 0 || strcmp (buf2, ".jpeg") == 0) {
        strcpy (buf2, "Content-Type: image/jpeg\r\n");
    }

    if ( strcmp(buf2, ".png") == 0 ) {
        strcpy (buf2, "Content-Type: image/png\r\n");
    }

    else if ( strcmp(buf2, ".gif") == 0) {
        strcpy (buf2, "Content-Type: image/gif\r\n");
    }

    else {
        strcpy (buf2, "Content-Type: application/octet-stream\r\n");
    }

    strcpy(p, buf2);
    return p;
}

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


char* render_img(char* filename){

    FILE* file =fopen(filename, "rb");

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
    printf("File size: %ld\n", file_size);
    char* temp = malloc(sizeof(char)*(file_size+1));
    

    int delta;

    while (file_size > 4096) {
        delta = fread(temp, 4096, 1, file);
        if (delta == 0) {
            /* handle error */
            fclose(file);
            /* need to refactor here; c_sock is useless and needs to be closed */
            return temp;
        }
        file_size -= delta;
    }
    if (file_size > 0) {
        /* last chunk; fread only returns a short count on an actual error so no loop here */
        int delta = fread(temp, 4096, 1, file);
        if (delta == 0) {
            /* handle error */
            fclose(file);
            /* need to refactor here; c_sock is useless and needs to be closed */
            return temp;
        }
    }

    fclose(file);
    return temp; 
}