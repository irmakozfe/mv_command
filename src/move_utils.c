#include "../include/move_utils.h"
#include "../include/globals.h"
#include "../include/file_utils.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h> 

int mvRenameFile(const char *source_file, const char *new_name) {
    printf("DEBUG: mvRenameFile() called with source_file='%s', new_name='%s'\n", source_file, new_name);

    if (!source_file || !new_name) {
        fprintf(stderr, "Error: mvRenameFile() received NULL parameters.\n");
        return -1;
    }

    if (!file_exists(source_file)) {
        fprintf(stderr, "Error: Source file '%s' does not exist.\n", source_file);
        return -1;
    }

    if (!option_force) {
        if (option_no_clobber && access(new_name, F_OK) == 0) {
            printf("DEBUG: -n flag detected, skipping move for '%s'\n", new_name);
            fprintf(stderr, "Warning: '%s' already exists, skipping due to -n option.\n", new_name);
            return 1;
        }
        if (option_interactive && access(new_name, F_OK) == 0) {
            printf("DEBUG: -i flag detected, asking for confirmation...\n");
            printf("overwrite '%s'? (y/n [n]): ", new_name);
            char response = getchar();
            while (getchar() != '\n');
            if (response != 'y' && response != 'Y') {
                printf("Skipped file: %s\n", new_name);
                return 1;
            }
            printf("DEBUG: User confirmed overwrite, removing '%s'\n", new_name);
            remove(new_name);
        }
    }

    if (option_force && access(new_name, F_OK) == 0) {
        printf("DEBUG: -f flag detected, removing existing file before rename.\n");
        if (remove(new_name) != 0) {
            perror("Error removing existing file before rename");
            return -1;
        }
    }

    if (option_backup && access(new_name, F_OK) == 0) {
        char backup_name[4096];
        snprintf(backup_name, sizeof(backup_name), "%s~", new_name);
        remove(backup_name);
        printf("DEBUG: -b flag detected, creating backup for '%s'\n", new_name);
        if (rename(new_name, backup_name) != 0) {
            perror("Backup creation failed");
            return -1;
        } else {
            printf("Backup created: %s -> %s\n", new_name, backup_name);
        }
    }

    if (rename(source_file, new_name) == 0) {
        if (option_verbose) {
            printf("DEBUG: -v flag detected, printing move action...\n");
            printf("renamed: %s -> %s\n", source_file, new_name);
        }
        return 0;
    } else {
        perror("Rename failed");
        return -1;
    }
}

int mvMoveFileToDir(const char *source, const char *destination_dir) {
    printf("DEBUG: mvMoveFileToDir() called with source='%s', destination_dir='%s'\n", source, destination_dir);

    if (!source || !destination_dir) {
        fprintf(stderr, "Error: mvMoveFileToDir() received NULL parameters.\n");
        return -1;
    }

    if (!file_exists(source)) {
        fprintf(stderr, "Error: Source file '%s' does not exist.\n", source);
        return -1;
    }

    char destination[4096];
    snprintf(destination, sizeof(destination), "%s/%s", destination_dir, strrchr(source, '/') ? strrchr(source, '/') + 1 : source);

    if (option_no_clobber && access(destination, F_OK) == 0) {
        printf("DEBUG: -n flag detected, skipping move for '%s'\n", destination);
        return 1;
    }

    if (option_backup && access(destination, F_OK) == 0) {
        char backup_name[4096];
        snprintf(backup_name, sizeof(backup_name), "%s~", destination);
        remove(backup_name);
        printf("DEBUG: -b flag detected, creating backup before move\n");
        if (rename(destination, backup_name) != 0) {
            perror("Backup creation failed before move");
            return -1;
        }
    }

    if (rename(source, destination) == 0) {
        if (option_verbose) {
            printf("DEBUG: -v flag detected, printing move action...\n");
            printf("renamed: %s -> %s\n", source, destination);
        }
        return 0;
    } else {
        perror("Error moving file");
        return -1;
    }

}

int mvMoveDirToDir(const char *source_dir, const char *target_dir) {
    printf("DEBUG: mvMoveDirToDir() called with source_dir='%s', target_dir='%s'\n", source_dir, target_dir);

    if (!source_dir || !target_dir) {
        fprintf(stderr, "Error: mvMoveDirToDir() received NULL parameters.\n");
        return -1;
    }

    char target_path[4096];
    snprintf(target_path, sizeof(target_path), "%s/%s", target_dir, strrchr(source_dir, '/') ? strrchr(source_dir, '/') + 1 : source_dir);

    if (option_backup && access(target_path, F_OK) == 0) {
        char backup_name[4096];
        snprintf(backup_name, sizeof(backup_name) - 1, "%s~", target_path);
        remove(backup_name);
        printf("DEBUG: -b flag detected, creating backup before moving directory\n");
        if (rename(target_path, backup_name) != 0) {
            perror("Error creating backup before moving directory");
            return -1;
        }
    }

    if (!option_force) {
        if (option_no_clobber && access(target_path, F_OK) == 0) {
            printf("DEBUG: -n flag detected, skipping move for '%s'\n", target_path);
            fprintf(stderr, "Warning: '%s' already exists, skipping due to -n option.\n", target_path);
            return 1;
        }

        if (option_interactive && access(target_path, F_OK) == 0) {
            printf("DEBUG: -i flag detected, asking for confirmation...\n");
            printf("overwrite '%s'? (y/n [n]): ", target_path);
            char response = getchar();
            while (getchar() != '\n');
            if (response != 'y' && response != 'Y') {
                printf("Skipped directory: %s\n", target_path);
                return 1;
            }
            printf("DEBUG: User confirmed overwrite, removing directory '%s'\n", target_path);
            rmdir(target_path);
        }
    }

    if (rename(source_dir, target_path) == 0) {
        if (option_verbose) {
            printf("DEBUG: -v flag detected, printing move action...\n");
            printf("renamed: %s -> %s\n", source_dir, target_path);
        }
        return 0;
    } else {
        perror("Error renaming directory");
        return -1;
    }

    if (rename(source_dir, target_dir) == 0) {
        if (option_verbose) {
            printf("renamed: %s -> %s\n", source_dir, target_dir);
        }
        return 0;
    } else {
        perror("Recursive move failed");
        return -1;
    }
}

int mvRenameDir(const char *source_dir, const char *new_name) {
    printf("DEBUG: mvRenameDir() called with source_dir='%s', new_name='%s'\n", source_dir, new_name);

    if (!source_dir || !new_name) {
        fprintf(stderr, "Error: mvRenameDir() received NULL parameters.\n");
        return -1;
    }

    if (rename(source_dir, new_name) == 0) {
        if (option_verbose) {
            printf("DEBUG: -v flag detected, printing move action...\n");
            printf("renamed: %s -> %s\n", source_dir, new_name);
        }
        return 0;
    } else {
        perror("Error renaming directory");
        return -1;
    }
}
