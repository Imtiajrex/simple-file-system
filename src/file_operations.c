#include "filesystem.h"
#include "file_operations.h"
#include "file_utils.h"

// Create a new file with optional tags
int create_file(const char* filename, const char* tags[], int tag_count) {
    if (!fs) {
        printf("Filesystem not initialized\n");
        return -1;
    }

    // Check if filename already exists
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used && 
            strcmp(fs->file_table[i].filename, filename) == 0) {
            printf("File already exists: %s\n", filename);
            return -1;
        }
    }

    // Find free file entry
    for (int i = 0; i < MAX_FILES; i++) {
        if (!fs->file_table[i].is_used) {
            strncpy(fs->file_table[i].filename, filename, MAX_FILENAME_LENGTH - 1);
            
            // Extract and set extension
            extract_extension(filename, fs->file_table[i].extension);
            
            // Determine and set file type
            fs->file_table[i].file_type = determine_file_type(fs->file_table[i].extension);
            strncpy(
                fs->file_table[i].file_type_str, 
                get_file_type_string(fs->file_table[i].file_type),
                MAX_FILE_TYPE_LENGTH
            );

            // Add tags
            fs->file_table[i].tag_count = (tag_count > MAX_TAGS) ? MAX_TAGS : tag_count;
            for (int j = 0; j < fs->file_table[i].tag_count; j++) {
                strncpy(fs->file_table[i].tags[j], tags[j], MAX_TAG_LENGTH - 1);
            }

            fs->file_table[i].creation_time = time(NULL);
            fs->file_table[i].modification_time = time(NULL);
            fs->file_table[i].file_size = 0;
            fs->file_table[i].start_block = fs->next_free_block++;
            fs->file_table[i].is_used = 1;
            
            printf("Created file: %s (Type: %s, Extension: %s)\n", 
                   filename, 
                   fs->file_table[i].file_type_str, 
                   fs->file_table[i].extension);
            return i;
        }
    }

    printf("Cannot create file. Filesystem full.\n");
    return -1;
}

// Remove a file
int remove_file(const char* filename) {
    if (!fs) {
        printf("Filesystem not initialized\n");
        return -1;
    }

    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used && 
            strcmp(fs->file_table[i].filename, filename) == 0) {
            // Mark file as unused
            fs->file_table[i].is_used = 0;
            memset(fs->data + (fs->file_table[i].start_block * BLOCK_SIZE), 0, BLOCK_SIZE);
            printf("Removed file: %s\n", filename);
            return 0;
        }
    }

    printf("File not found: %s\n", filename);
    return -1;
}

// Write content to a file
int write_file(const char* filename, const char* content) {
    int file_index = -1;

    // Find the file
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used && 
            strcmp(fs->file_table[i].filename, filename) == 0) {
            file_index = i;
            break;
        }
    }

    if (file_index == -1) {
        printf("File not found: %s\n", filename);
        return -1;
    }

    size_t content_length = strlen(content);
    if (content_length > BLOCK_SIZE) {
        printf("File too large for block size\n");
        return -1;
    }

    // Write content to file's block
    int start_block = fs->file_table[file_index].start_block;
    memcpy(fs->data + (start_block * BLOCK_SIZE), content, content_length);
    
    // Update file metadata
    fs->file_table[file_index].file_size = content_length;
    fs->file_table[file_index].modification_time = time(NULL);

    printf("Written %zu bytes to file: %s\n", content_length, filename);
    return 0;
}

// Read file content
char* read_file(const char* filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used && 
            strcmp(fs->file_table[i].filename, filename) == 0) {
            
            char* content = malloc(BLOCK_SIZE + 1);
            if (!content) {
                printf("Memory allocation failed\n");
                return NULL;
            }

            int start_block = fs->file_table[i].start_block;
            memcpy(content, fs->data + (start_block * BLOCK_SIZE), BLOCK_SIZE);
            content[BLOCK_SIZE] = '\0';  // Null terminate

            return content;
        }
    }

    printf("File not found: %s\n", filename);
    return NULL;
}

// Get file size
int get_file_size(const char* filename) {
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used && 
            strcmp(fs->file_table[i].filename, filename) == 0) {
            return fs->file_table[i].file_size;
        }
    }

    printf("File not found: %s\n", filename);
    return -1;
}

// List all files
void list_files() {
    printf("Files in filesystem:\n");
    for (int i = 0; i < MAX_FILES; i++) {
        if (fs->file_table[i].is_used) {
            printf("- %s (size: %zu bytes, type: %s)\n", 
                   fs->file_table[i].filename, 
                   fs->file_table[i].file_size,
                   fs->file_table[i].file_type_str);
        }
    }
}