#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filesystem.h"
#include "file_operations.h"
#include "search_filter.h"
#include "file_utils.h"

// Interactive shell
void filesystem_shell() {
    char command[256];
    char arg1[256];
    char arg2[256];

    while (1) {
        printf("filesystem> ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = 0;  // Remove newline

        // Parse command
        if (sscanf(command, "%s %s %[^\n]", arg1, arg2, arg2) == 2) {
            // Two-argument commands
            if (strcmp(arg1, "touch") == 0) {
                // Example of creating a file with tags
                const char* tags[] = {"draft", "work"};
                create_file(arg2, tags, 2);
            } else if (strcmp(arg1, "rm") == 0) {
                remove_file(arg2);
            } else if (strcmp(arg1, "write") == 0) {
                char content[BLOCK_SIZE];
                printf("Enter file content: ");
                fgets(content, sizeof(content), stdin);
                content[strcspn(content, "\n")] = 0;
                write_file(arg2, content);
            } else if (strcmp(arg1, "read") == 0) {
                char* content = read_file(arg2);
                if (content) {
                    printf("File content: %s\n", content);
                    free(content);
                }
            } else if (strcmp(arg1, "size") == 0) {
                int size = get_file_size(arg2);
                if (size != -1) {
                    printf("File size: %d bytes\n", size);
                }
            } else if (strcmp(arg1, "search") == 0) {
                search_files_by_name(arg2);
            } else if (strcmp(arg1, "filter-ext") == 0) {
                filter_files_by_extension(arg2);
            } else if (strcmp(arg1, "filter-tag") == 0) {
                filter_files_by_tag(arg2);
            }
        } else if (sscanf(command, "%s %s", arg1, arg2) == 2) {
            if (strcmp(arg1, "filter-type") == 0) {
                // Parse file type
                FileType type = FILE_TYPE_UNKNOWN;
                if (strcmp(arg2, "text") == 0) type = FILE_TYPE_TEXT;
                else if (strcmp(arg2, "binary") == 0) type = FILE_TYPE_BINARY;
                else if (strcmp(arg2, "image") == 0) type = FILE_TYPE_IMAGE;
                else if (strcmp(arg2, "document") == 0) type = FILE_TYPE_DOCUMENT;
                else if (strcmp(arg2, "spreadsheet") == 0) type = FILE_TYPE_SPREADSHEET;
                else if (strcmp(arg2, "audio") == 0) type = FILE_TYPE_AUDIO;
                else if (strcmp(arg2, "video") == 0) type = FILE_TYPE_VIDEO;
                
                filter_files_by_type(type);
            }
        } else if (sscanf(command, "%s", arg1) == 1) {
            // Single-argument commands
            if (strcmp(arg1, "ls") == 0) {
                list_files();
            } else if (strcmp(arg1, "format") == 0) {
                format_filesystem();
            } else if (strcmp(arg1, "exit") == 0) {
                break;
            }
        }
    }
}

int main() {
    // Initialize filesystem
    create_filesystem();

    printf("Enhanced Filesystem Shell\n");
    printf("Commands:\n");
    printf("  touch [filename]   - Create a new file\n");
    printf("  rm [filename]      - Remove a file\n");
    printf("  write [filename]   - Write content to a file\n");
    printf("  read [filename]    - Read file contents\n");
    printf("  size [filename]    - Get file size\n");
    printf("  ls                 - List all files\n");
    printf("  search [term]      - Search files by name\n");
    printf("  filter-ext [ext]   - Filter files by extension\n");
    printf("  filter-type [type] - Filter files by type\n");
    printf("  filter-tag [tag]   - Filter files by tag\n");
    printf("  format             - Reset filesystem\n");
    printf("  exit               - Exit shell\n");

    // Start interactive shell
    filesystem_shell();

    // Cleanup
    destroy_filesystem(fs);
    return 0;
}