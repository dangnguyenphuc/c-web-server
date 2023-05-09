#ifndef RESPONSE_H
#define RESPONSE_H

unsigned long getFileSize(char* fileName);
char* find_type(char* filename);
char* render_template(char* filename);
char* render_img(char* filename);

#endif