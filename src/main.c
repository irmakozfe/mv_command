#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "/Users/buseokcu/CLionProjects/deneme2/include/move_utils.h"
#include "/Users/buseokcu/CLionProjects/deneme2/include/file_utils.h"
#include "/Users/buseokcu/CLionProjects/deneme2/include/linked_list.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1; // Hatalı kullanım
    }

    if(argc > 3) {
        const char *destination = argv[argc - 1]; // Son argüman hedef dizin
        Node *head = NULL; // Bağlı liste başı

        for(int i = 1; i < argc; i++) {
            append_node(&head, argv[i]);
        }

        Node *current = head;
        while (current->next != NULL) {
            const char *source = current->file_path;

            int source_is_file = !is_file(source);
            int destination_is_file = !is_file(destination);

            // 1. Durum: Kaynak dosya, hedef dizin
            if (source_is_file && !destination_is_file) {
                if (mvMoveFileToDir(source, destination) == 0) {
                    printf("File '%s' moved to directory '%s'\n", source, destination);
                } else {
                    fprintf(stderr, "Failed to move file '%s' to directory '%s'.\n", source, destination);
                }
            }else if(!source_is_file && !destination_is_file) {
                if (mvMoveDirToDir(source, destination) == 0) {
                    printf("Directory '%s' moved to directory '%s'\n", source, destination);
                } else {
                    fprintf(stderr, "Failed to move directory to directory.\n");
                }
            }else {
                fprintf(stderr, "Source '%s' is not a valid file.\n", source);
            }

            current = current->next; // Sonraki düğüme geç
        }

        // Bağlı listeyi serbest bırak
        free_list(head);

        return 0;
    }

    else {
        const char *source = argv[1];
        const char *destination = argv[2];

        // Dosya mı yoksa dizin mi olduğunu kontrol et
        int source_is_file = !is_file(source);
        int destination_is_file = !is_file(destination);

        // 1. Durum: Her ikisi de dosya
        if (source_is_file && destination_is_file) {
            if (mvRenameFile(source, destination) == 0) {
                printf("File renamed from '%s' to '%s'\n", source, destination);
            } else {
                fprintf(stderr, "Failed to rename file.\n");
            }
        }
        // 2. Durum: Her ikisi de dizin
        else if (!source_is_file && !destination_is_file) {
            if (file_exists(destination)) {
                if (mvMoveDirToDir(source, destination) == 0) {
                    printf("Directory '%s' moved to directory '%s'\n", source, destination);
                } else {
                    fprintf(stderr, "Failed to move directory to directory.\n");
                }
            }else {
                if (mvRenameDir(source, destination) == 0) {
                    printf("Directory renamed from '%s' to '%s'\n", source, destination);
                } else {
                    fprintf(stderr, "Failed to rename directory.\n");
                }
            }

        }
        // 3. Durum: Kaynak dosya, hedef dizin
        else if (source_is_file && !destination_is_file) {
            if (mvMoveFileToDir(source, destination) == 0) {
                printf("File '%s' moved to directory '%s'\n", source, destination);
            } else {
                fprintf(stderr, "Failed to move file to directory.\n");
            }
        }

        return 0; // Başarılı
    }
}