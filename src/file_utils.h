#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "filesystem.h"

void extract_extension(const char* filename, char* extension);
FileType determine_file_type(const char* extension);
const char* get_file_type_string(FileType type);

#endif 