#include "filesystem.h"

// Global filesystem instance
FileSystem* fs = NULL;

// Create a new filesystem
FileSystem* create_filesystem() {
    fs = (FileSystem*)malloc(sizeof(FileSystem));
    if (fs == NULL) {
        printf("Memory allocation failed for filesystem\n");
        return NULL;
    }

    // Initialize filesystem
    memset(fs->data, 0, FILESYSTEM_SIZE);
    memset(fs->file_table, 0, sizeof(fs->file_table));
    fs->next_free_block = 0;
    fs->total_blocks = FILESYSTEM_SIZE / BLOCK_SIZE;

    return fs;
}

// Destroy the filesystem
void destroy_filesystem(FileSystem* fs) {
    if (fs) {
        free(fs);
    }
}

// Format filesystem
void format_filesystem() {
    if (fs) {
        memset(fs->data, 0, FILESYSTEM_SIZE);
        memset(fs->file_table, 0, sizeof(fs->file_table));
        fs->next_free_block = 0;
        printf("Filesystem formatted\n");
    }
}