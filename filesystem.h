#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define BLOCK_SIZE 512
#define MAX_FILENAME_LEN 255
#define MAX_FILES 100

int createFile(const char *filename, const char *filepath, int size);
int deleteFile(const char *filename, const char *filepath);
void readFile(const char *filename, const char *filepath);
void writeFile(const char *filename, const char *directory, const char *data);
void rewriteFile(const char *filename, const char *filepath, const char *data);

#endif
