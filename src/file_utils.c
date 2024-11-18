#include <ctype.h>
#include "file_utils.h"

// Extract file extension and convert to lowercase
void extract_extension(const char* filename, char* extension) {
    char* dot = strrchr(filename, '.');
    if (dot && dot != filename) {
        strncpy(extension, dot + 1, 15);
        extension[15] = '\0';
        // Convert to lowercase
        for (int i = 0; extension[i]; i++) {
            extension[i] = tolower(extension[i]);
        }
    } else {
        extension[0] = '\0';
    }
}

// Determine file type based on extension
FileType determine_file_type(const char* extension) {
    if (!extension || strlen(extension) == 0) return FILE_TYPE_UNKNOWN;

    struct {
        const char* ext;
        FileType type;
    } type_map[] = {
        {"txt", FILE_TYPE_TEXT},
        {"csv", FILE_TYPE_SPREADSHEET},
        {"doc", FILE_TYPE_DOCUMENT},
        {"docx", FILE_TYPE_DOCUMENT},
        {"pdf", FILE_TYPE_DOCUMENT},
        {"jpg", FILE_TYPE_IMAGE},
        {"jpeg", FILE_TYPE_IMAGE},
        {"png", FILE_TYPE_IMAGE},
        {"gif", FILE_TYPE_IMAGE},
        {"mp3", FILE_TYPE_AUDIO},
        {"wav", FILE_TYPE_AUDIO},
        {"mp4", FILE_TYPE_VIDEO},
        {"avi", FILE_TYPE_VIDEO}
    };

    for (size_t i = 0; i < sizeof(type_map) / sizeof(type_map[0]); i++) {
        if (strcmp(extension, type_map[i].ext) == 0) {
            return type_map[i].type;
        }
    }

    return FILE_TYPE_BINARY;
}

// Get file type string representation
const char* get_file_type_string(FileType type) {
    switch (type) {
        case FILE_TYPE_TEXT: return "Text";
        case FILE_TYPE_BINARY: return "Binary";
        case FILE_TYPE_IMAGE: return "Image";
        case FILE_TYPE_DOCUMENT: return "Document";
        case FILE_TYPE_SPREADSHEET: return "Spreadsheet";
        case FILE_TYPE_AUDIO: return "Audio";
        case FILE_TYPE_VIDEO: return "Video";
        default: return "Unknown";
    }
}