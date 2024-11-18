#ifndef SEARCH_FILTER_H
#define SEARCH_FILTER_H

#include "filesystem.h"

void search_files_by_name(const char* search_term);
void filter_files_by_extension(const char* extension);
void filter_files_by_type(FileType type);
void filter_files_by_tag(const char* tag);

#endif 