#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <getopt.h>
#include "../include/move_utils.h"
#include "../include/file_utils.h"
#include "../include/linked_list.h"
#include "../include/globals.h"
#include <semaphore.h>
#include <string.h>
#define BUFFER_SIZE 4096

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

void read_from_stdin(char *buffer, size_t size) {
    if (fgets(buffer, size, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0'; // Yeni satır karakterini kaldır
        }
    }
}

void print_help() {
    printf("usage: mv [-f | -i | -n] [-hv] source target\n");
    printf("\tmv [-f | -i | -n] [-v] source ... directory\n\n");
    printf("Options:\n");
    printf("  -f   Force move without confirmation\n");
    printf("  -i   Interactive mode, prompt before overwrite\n");
    printf("  -n   No-clobber mode, do not overwrite existing files\n");
    printf("  -v   Verbose mode, display actions\n");
    printf("  -b   Backup existing files before overwrite\n");
    printf("  -h   Display this help message\n");
}

//bayraklari ayristirmak icin
void parse_flags(int argc, char *argv[], int *non_flag_index) {
    int opt;
    while ((opt = getopt_long(argc, argv, "finvbh", long_options, NULL)) != -1) {
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
            case '?': 
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
    pthread_mutex_init(&resource_semaphore, NULL); 
    char buffer[BUFFER_SIZE];

    int non_flag_index = -1; 
    parse_flags(argc, argv, &non_flag_index);

    

    if (argc == 2) {
        const char *destination = argv[1];

        read_from_stdin(buffer, BUFFER_SIZE);
        const char *source = buffer; 

        int source_is_file = !is_file(source);
        int destination_is_file = !is_file(destination);

        if (source_is_file && !destination_is_file) {
            if (mvMoveFileToDir(source, destination) == 0) {
                printf("File '%s' moved to directory '%s'\n", source, destination);
            } else {
                fprintf(stderr, "Failed to move file to directory '%s'\n", destination);
            }
        }
        else if (!source_is_file && !destination_is_file) {
            if (mvMoveDirToDir(source, destination) == 0) {
                printf("Directory '%s' moved to directory '%s'\n", source, destination);
            } else {
                fprintf(stderr, "Failed to move directory '%s'\n", source);
            }
        }
        else {
            fprintf(stderr, "Invalid source and destination combination.\n");
        }

        pthread_mutex_destroy(&resource_semaphore);
        return 0; 
    }
    if (argc == 2 && option_help) {
        print_help();
        return 0; 
    }

    if (argc < 3) {
        print_help();
        return 1;
    }

    if (non_flag_index == -1 || argc - non_flag_index < 2) {
        fprintf(stderr, "Error: Missing source or destination arguments.\n");
        return 1;
    }

    const char *source = argv[non_flag_index];
    const char *destination = argv[argc - 1];

    if (argc - non_flag_index > 2) {
        const char *destination = argv[argc - 1]; 
        Node *head = NULL; 

        for (int i = non_flag_index; i < argc - 1; i++) {
            append_node(&head, argv[i]);
        }

        pthread_t threads[argc - non_flag_index - 1]; 
        int thread_count = 0;

        Node *current = head;
        while (current != NULL) {
            thread_args_t *args = malloc(sizeof(thread_args_t));
            if (!args) {
                fprintf(stderr, "Memory allocation failed.\n");
                free_list(head);
                return 1;
            }

            args->source = current->file_path;
            args->destination = destination;
            args->is_file = !is_file(current->file_path);

            if (pthread_create(&threads[thread_count], NULL, thread_function, (void *)args) != 0) {
                fprintf(stderr, "Error creating thread.\n");
                free(args);
                free_list(head);
                return 1;
            }

            current = current->next; 
            thread_count++;
        }
        for (int i = 0; i < thread_count; i++) {
            pthread_join(threads[i], NULL);
        }

        free_list(head);

        printf("All tasks completed successfully.\n");
        return 0;
    } else {

        int source_is_file = !is_file(source);
        int destination_is_file = !is_file(destination);

        if (source_is_file && destination_is_file) {
            if (mvRenameFile(source, destination) == 0) {
            } else {
                fprintf(stderr, "Failed to rename file.\n");
            }
        }

        else if (!source_is_file && !destination_is_file) {
            if (file_exists(destination)) {
                if (mvMoveDirToDir(source, destination) == 0) {
                } else {
                    fprintf(stderr, "Failed to move directory to directory.\n");
                }
                
            } else {
                if (mvRenameDir(source, destination) == 0) {
                } else {
                    fprintf(stderr, "Failed to rename directory.\n");
                }
            }

        }
        else if (source_is_file && !destination_is_file) {
            if (mvMoveFileToDir(source, destination) == 0) {
            } else {
                fprintf(stderr, "Failed to move file to directory.\n");
            }
        }

        pthread_mutex_destroy(&resource_semaphore);
        return 0; 
    }

}
