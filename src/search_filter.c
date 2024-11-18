#include "filesystem.h"
#include "search_filter.h"
#include "file_utils.h"

void search_files_by_name(const char* search_term) {
    printf("Search results for '%s':\n", search_term);
    int found = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used && 
            strstr(fs->file_table[i].filename, search_term) != NULL) {
            printf("- %s (Type: %s, Size: %zu bytes)\n", 
                   fs->file_table[i].filename, 
                   fs->file_table[i].file_type_str, 
                   fs->file_table[i].file_size);
            found++;
        }
    }
    if (found == 0) {
        printf("No files found matching the search term.\n");
    }
}

void filter_files_by_extension(const char* extension) {
    printf("Files with extension '%s':\n", extension);
    int found = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used && 
            strcmp(fs->file_table[i].extension, extension) == 0) {
            printf("- %s (Size: %zu bytes)\n", 
                   fs->file_table[i].filename, 
                   fs->file_table[i].file_size);
            found++;
        }
    }
    if (found == 0) {
        printf("No files found with extension '%s'.\n", extension);
    }
}

void filter_files_by_type(FileType type) {
    const char* type_name = get_file_type_string(type);
    printf("Files of type '%s':\n", type_name);
    
    int found = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used && fs->file_table[i].file_type == type) {
            printf("- %s (Extension: %s, Size: %zu bytes)\n", 
                   fs->file_table[i].filename, 
                   fs->file_table[i].extension, 
                   fs->file_table[i].file_size);
            found++;
        }
    }
    if (found == 0) {
        printf("No files found of type '%s'.\n", type_name);
    }
}

void filter_files_by_tag(const char* tag) {
    printf("Files tagged with '%s':\n", tag);
    int found = 0;
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used) {
            for (int j = 0; j < fs->file_table[i].tag_count; j++) {
                if (strcmp(fs->file_table[i].tags[j], tag) == 0) {
                    printf("- %s (Type: %s, Size: %zu bytes)\n", 
                           fs->file_table[i].filename, 
                           fs->file_table[i].file_type_str, 
                           fs->file_table[i].file_size);
                    found++;
                    break;
                }
            }
        }
    }
    if (found == 0) {
        printf("No files found with tag '%s'.\n", tag);
    }
}