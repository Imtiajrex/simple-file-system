#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include "filesystem.h"

// File operation functions
int create_file(const char* filename, const char* tags[], int tag_count);
int remove_file(const char* filename);
int write_file(const char* filename, const char* content);
char* read_file(const char* filename);
int get_file_size(const char* filename);
void list_files();

#endif // FILE_OPERATIONS_H