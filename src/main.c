#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <getopt.h>
#include "../include/move_utils.h"
#include "../include/file_utils.h"
#include "../include/linked_list.h"
#include "../include/globals.h"
#include <semaphore.h>

pthread_mutex_t resource_semaphore;

// Thread argümanları için yapı
typedef struct {
    const char *source;
    const char *destination;
    int is_file;
} thread_args_t;

// Thread fonksiyonu
void *thread_function(void *arg) {
    thread_args_t *args = (thread_args_t *)arg;

    pthread_mutex_lock(&resource_semaphore); // Kaynağı kilitle

    // Dosya mı yoksa dizin mi kontrol et
    if (args->is_file) {
        if (mvMoveFileToDir(args->source, args->destination) == 0) {
            //printf("File '%s' moved to '%s'\n", args->source, args->destination);
        } else {
            fprintf(stderr, "Failed to move file '%s'\n", args->source);
        }
    } else {
        if (mvMoveDirToDir(args->source, args->destination) == 0) {
            //printf("Directory '%s' moved to '%s'\n", args->source, args->destination);
        } else {
            fprintf(stderr, "Failed to move directory '%s'\n", args->source);
        }
    }
    pthread_mutex_unlock(&resource_semaphore); // Kaynağı serbest bırak
    free(args); // Dinamik belleği serbest bırak
    return NULL;
}

void print_help() {
    printf("usage: ./mv [-f | -i | -n] [-hv] source target\n");
    printf("\t./mv [-f | -i | -n] [-v] source ... directory\n\n");
}

//bayraklari ayristirmak icin
void parse_flags(int argc, char *argv[], int *non_flag_index) {
    int opt;
    while ((opt = getopt_long(argc, argv, "finvhb", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                option_force = 1;
            break;
            case 'i':
                option_interactive = 1;
            break;
            case 'n':
                option_no_clobber = 1;
            break;
            case 'v':
                option_verbose = 1;
            break;
            case 'b':
                option_backup = 1;
            break;
            case 'h':
                option_help = 1;
            break;
            case '?': // Geçersiz bayrak
                default:
                    fprintf(stderr, "mv: illegal option\n");
            print_help();
            exit(1);
        }
    }

    // İlk bayrak olmayan argümanı belirle
    *non_flag_index = optind;
}



int main(int argc, char *argv[]) {
    pthread_mutex_init(&resource_semaphore, NULL); // Aynı anda 2 thread erişebilir

    ///yeni
    int non_flag_index = -1; // Bayrak olmayan ilk argümanın indeksini tutacak
    parse_flags(argc, argv, &non_flag_index);

    if (argc == 2 && option_help) {
        print_help();
        return 0; // Başarılı sonlanma
    }


    if (argc < 3) {
        print_help();
        return 1; // Hatalı kullanım
    }


    if (non_flag_index == -1 || argc - non_flag_index < 2) {
        fprintf(stderr, "Error: Missing source or destination arguments.\n");
        return 1;
    }

    const char *source = argv[non_flag_index];
    const char *destination = argv[argc - 1];

    ////yeni

    if (argc - non_flag_index > 2) {
        const char *destination = argv[argc - 1]; // Son argüman hedef dizin
        Node *head = NULL; // Bağlı liste başı

        for (int i = non_flag_index; i < argc - 1; i++) {
            append_node(&head, argv[i]);
        }

        pthread_t threads[argc - non_flag_index - 1]; // Kaynak dosyalar kadar thread
        int thread_count = 0;

        Node *current = head;
        while (current != NULL) {
            // Thread argümanlarını oluştur
            thread_args_t *args = malloc(sizeof(thread_args_t));
            if (!args) {
                fprintf(stderr, "Memory allocation failed.\n");
                free_list(head);
                return 1;
            }

            args->source = current->file_path;
            args->destination = destination;
            args->is_file = !is_file(current->file_path);

            // Thread oluştur
            if (pthread_create(&threads[thread_count], NULL, thread_function, (void *)args) != 0) {
                fprintf(stderr, "Error creating thread.\n");
                free(args);
                free_list(head);
                return 1;
            }

            current = current->next; // Sonraki düğüme geç
            thread_count++;
        }

        // Tüm thread'lerin tamamlanmasını bekle
        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }

        // Bağlı listeyi serbest bırak
        free_list(head);

        printf("All tasks completed successfully.\n");
        return 0;
    } else {

        // Dosya mı yoksa dizin mi olduğunu kontrol et
        int source_is_file = !is_file(source);
        int destination_is_file = !is_file(destination);

        // 1. Durum: Her ikisi de dosya
        if (source_is_file && destination_is_file) {
            if (mvRenameFile(source, destination) == 0) {
                //printf("File renamed from '%s' to '%s'\n", source, destination);
            } else {
                fprintf(stderr, "Failed to rename file.\n");
            }
        }
        // 2. Durum: Her ikisi de dizin
        else if (!source_is_file && !destination_is_file) {
            if (file_exists(destination)) {
                if (mvMoveDirToDir(source, destination) == 0) {
                    //printf("Directory '%s' moved to directory '%s'\n", source, destination);
                } else {
                    fprintf(stderr, "Failed to move directory to directory.\n");
                }
            } else {
                if (mvRenameDir(source, destination) == 0) {
                    //printf("Directory renamed from '%s' to '%s'\n", source, destination);
                } else {
                    fprintf(stderr, "Failed to rename directory.\n");
                }
            }

        }
        // 3. Durum: Kaynak dosya, hedef dizin
        else if (source_is_file && !destination_is_file) {
            if (mvMoveFileToDir(source, destination) == 0) {
                //printf("File '%s' moved to directory '%s'\n", source, destination);
            } else {
                fprintf(stderr, "Failed to move file to directory.\n");
            }
        }

        pthread_mutex_destroy(&resource_semaphore);
        return 0; // Başarılı
    }
}