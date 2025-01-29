#include "../include/move_utils.h"
#include "../include/globals.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int mvRenameFile(const char *source_file, const char *new_name) {


  if (!option_force) {
        if (option_no_clobber && access(new_name, F_OK) == 0) {
            if (option_verbose) {
                printf("'%s' not overwritten\n", new_name);
            }
            return 1; // İşlem iptal edildi
        }

        if (option_interactive && access(new_name, F_OK) == 0) {
            printf("overwrite '%s'? (y/n [n]): ", new_name);
            char response = getchar();
            while (getchar() != '\n'); // Giriş tamponunu temizle
            if (response != 'y' && response != 'Y') {
                printf("not overwritten\n");
                return 1; // İşlem iptal edildi
            }
        }
    }

    // Eğer -b bayrağı aktifse ve hedef dosya mevcutsa
    if (option_backup && access(new_name, F_OK) == 0) {
        char backup_name[4096];
        snprintf(backup_name, sizeof(backup_name), "%s~", new_name);

        // Hedef dosyanın yedeğini oluştur
        if (rename(new_name, backup_name) != 0) {
            perror("mv: backup creation failed");
            return -1; // Yedekleme başarısız
        }

        if (option_verbose) {
            printf("%s -> %s (backup: '%s~')\n", source_file, new_name, backup_name);
        }
    }

    if (rename(source_file, new_name) == 0) {
      if (option_verbose && !option_backup) {
            printf("%s -> %s\n", source_file, new_name);
        }
        return 0; // Başarılı
    } else {
        char error_message[512];
		snprintf(error_message, sizeof(error_message), "mv: rename %s to %s", source_file, new_name);
		perror(error_message);
        return -1; // Hata
    }
}

int mvRenameDir(const char *source_dir, const char *new_name) {
    if (rename(source_dir, new_name) == 0) {
      if (option_verbose) {
            printf("%s -> %s\n", source_dir, new_name);
        }
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
    
	if (option_force) {
        if (access(destination, F_OK) == 0) { 
            if (remove(destination) != 0) {
                perror("Error removing existing file before move");
                return 1; 
            }
        }
    } else {
        if (option_no_clobber && access(destination, F_OK) == 0) {
                printf("'%s' not overwritten\n", destination);
            	return 0; // İşlem iptal edildi
        }

        if (option_interactive && access(destination, F_OK) == 0) {
            printf("overwrite '%s'? (y/n [n]): ", destination);
            char response = getchar();
            while (getchar() != '\n'); // Giriş tamponunu temizle
            if (response != 'y' && response != 'Y') {
		    if (remove(destination) != 0) { // Eğer kullanıcı onay verdiyse hedefi sil
                    perror("Error removing existing file after user confirmation");
                    return 1; // Silme başarısız
                }
	    }else {
                printf("not overwritten\n");
                return 1; // İşlem iptal edildi
            }
        }
    }

    // Dosyayı taşımayı dene
    if (rename(source, destination) == 0) {
      if (option_verbose) {
            printf("Moved: %s -> %s\n", source, destination);
        }
        return 0; // Taşıma başarılı
    } else {
	fprintf(stderr, "Error moving file: %s -> %s\n", source, destination);
        perror("Error moving file");
        return 1; // Taşıma başarısız
    }
}


int mvMoveDirToDir(const char *source_dir, const char *target_dir) {
    char target_path[4096];
    snprintf(target_path, sizeof(target_path), "%s/%s", target_dir, strrchr(source_dir, '/') ? strrchr(source_dir, '/') + 1 : source_dir);

    if (!option_force) {
        if (option_no_clobber && access(target_path, F_OK) == 0) {
            if (option_verbose) {
                printf("'%s' not overwritten\n", target_path);
            }
            return 1; // İşlem iptal edildi
        }

        if (option_interactive && access(target_path, F_OK) == 0) {
            printf("overwrite '%s'? (y/n [n]): ", target_path);
            char response = getchar();
            while (getchar() != '\n'); // Giriş tamponunu temizle
            if (response != 'y' && response != 'Y') {
                printf("not overwritten\n");
                return 1; // İşlem iptal edildi
            }
        }
    }

    if (rename(source_dir, target_path) == 0) {
      if (option_verbose) {
            printf("%s -> %s\n", source_dir, target_path);
        }
        return 0; // Başarılı
    } else {
        char error_message[512];
		snprintf(error_message, sizeof(error_message), "mv: rename %s to %s", source_dir, target_path);
		perror(error_message);
        return -1; // Hata
    }
}
