#include "/Users/buseokcu/CLionProjects/deneme2/include/move_utils.h"
#include <stdio.h>
#include <string.h>

int mvRenameFile(const char *source_file, const char *new_name) {
    if (rename(source_file, new_name) == 0) {
        return 0; // Başarılı
    } else {
        perror("Error renaming file");
        return -1; // Hata
    }
}

int mvRenameDir(const char *source_dir, const char *new_name) {
    if (rename(source_dir, new_name) == 0) {
        return 0; // Başarılı
    } else {
        perror("Error renaming directory");
        return -1; // Hata
    }
}

int mvMoveFileToDir(const char *source, const char *destination_dir) {
    char destination[4096];

    // Hedef dosya yolunu oluştur
    snprintf(destination, sizeof(destination), "%s/%s", destination_dir, strrchr(source, '/') ? strrchr(source, '/') + 1 : source);

    // Dosyayı taşımayı dene
    if (rename(source, destination) == 0) {
        return 0; // Taşıma başarılı
    } else {
        perror("Error moving file");
        return 1; // Taşıma başarısız
    }
}


int mvMoveDirToDir(const char *source_dir, const char *target_dir) {
    char target_path[4096];
    snprintf(target_path, sizeof(target_path), "%s/%s", target_dir, strrchr(source_dir, '/') ? strrchr(source_dir, '/') + 1 : source_dir);

    if (rename(source_dir, target_path) == 0) {
        return 0; // Başarılı
    } else {
        perror("Error moving directory to directory");
        return -1; // Hata
    }
}