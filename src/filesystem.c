#include "filesystem.h"

FileSystem* fs = NULL;

FileSystem* create_filesystem() {
    fs = (FileSystem*)malloc(sizeof(FileSystem));
    if (fs == NULL) {
        printf("Memory allocation failed for filesystem\n");
        return NULL;
    }

    memset(fs->data, 0, FILESYSTEM_SIZE);
    memset(fs->file_table, 0, sizeof(fs->file_table));
    fs->next_free_block = 0;
    fs->total_blocks = FILESYSTEM_SIZE / BLOCK_SIZE;

    return fs;
}

void destroy_filesystem(FileSystem* fs) {
    if (fs) {
        free(fs);
    }
}

void format_filesystem() {
    if (fs) {
        memset(fs->data, 0, FILESYSTEM_SIZE);
        memset(fs->file_table, 0, sizeof(fs->file_table));
        fs->next_free_block = 0;
        printf("Filesystem formatted\n");
    }
}