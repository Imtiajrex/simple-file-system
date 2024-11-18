#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILENAME_LENGTH 256
#define MAX_FILES 100
#define BLOCK_SIZE 1024
#define FILESYSTEM_SIZE (10 * 1024 * 1024)  // 10 MB
#define MAX_TAGS 5
#define MAX_TAG_LENGTH 32
#define MAX_FILE_TYPE_LENGTH 32

// File type enums
typedef enum {
    FILE_TYPE_UNKNOWN,
    FILE_TYPE_TEXT,
    FILE_TYPE_BINARY,
    FILE_TYPE_IMAGE,
    FILE_TYPE_DOCUMENT,
    FILE_TYPE_SPREADSHEET,
    FILE_TYPE_AUDIO,
    FILE_TYPE_VIDEO
} FileType;

// File entry structure
typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char extension[16];
    char file_type_str[MAX_FILE_TYPE_LENGTH];
    FileType file_type;
    char tags[MAX_TAGS][MAX_TAG_LENGTH];
    int tag_count;
    size_t file_size;
    time_t creation_time;
    time_t modification_time;
    int start_block;
    int is_used;
} FileEntry;

// Filesystem structure
typedef struct {
    char data[FILESYSTEM_SIZE];
    FileEntry file_table[MAX_FILES];
    int next_free_block;
    int total_blocks;
} FileSystem;

// Global filesystem instance
extern FileSystem* fs;

// Filesystem management functions
FileSystem* create_filesystem();
void destroy_filesystem(FileSystem* fs);
void format_filesystem();

#endif // FILESYSTEM_H