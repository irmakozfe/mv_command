#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../include/file_utils.h"

int file_exists(const char *filename) {
    if (!filename) {
        fprintf(stderr, "Error: file_exists() received a NULL filename.\n");
        return 0;
    }
    if (access(filename, F_OK) != 0) {
        perror("Error: Source file not found");
        return 0;
    }
    return 1;
}

int delete_file(const char *filename) {
    if (!filename) {
        fprintf(stderr, "Error: delete_file() received a NULL filename.\n");
        return -1;
    }
    if (remove(filename) != 0) {
        perror("Error deleting file");
        return -1;
    }
    return 0;
}

int is_file(const char *path) {
    if (!path) {
        fprintf(stderr, "Error: is_file() received a NULL path.\n");
        return 0;
    }
    size_t len = strlen(path);
    if (len < 4) {
        return 1;
    }
    return (path[len - 4] == '.') ? 0 : 1;
}
