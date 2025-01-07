#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "/Users/buseokcu/CLionProjects/mv_command/include/move_utils.h"
#include "/Users/buseokcu/CLionProjects/mv_command/include/file_utils.h"
#include "/Users/buseokcu/CLionProjects/mv_command/include/linked_list.h"
#include <semaphore.h>

pthread_mutex_t resource_semaphore;

typedef struct {
    const char *source;
    const char *destination;
    int is_file;
} thread_args_t;

void *thread_function(void *arg) {
    thread_args_t *args = (thread_args_t *)arg;

    pthread_mutex_lock(&resource_semaphore); 

    // Dosya mı yoksa dizin mi kontrol et
    if (args->is_file) {
        if (mvMoveFileToDir(args->source, args->destination) == 0) {
            printf("File '%s' moved to '%s'\n", args->source, args->destination);
        } else {
            fprintf(stderr, "Failed to move file '%s'\n", args->source);
        }
    } else {
        if (mvMoveDirToDir(args->source, args->destination) == 0) {
            printf("Directory '%s' moved to '%s'\n", args->source, args->destination);
        } else {
            fprintf(stderr, "Failed to move directory '%s'\n", args->source);
        }
    }
    pthread_mutex_unlock(&resource_semaphore); 
    free(args); 
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_mutex_init(&resource_semaphore, NULL); 
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <source1> <source2> ... <destination>\n", argv[0]);
        return 1; 
    }

    if (argc > 3) {
        const char *destination = argv[argc - 1]; 
        Node *head = NULL; 

        for (int i = 1; i < argc - 1; i++) {
            append_node(&head, argv[i]);
        }

        pthread_t threads[argc - 2]; 
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
        const char *source = argv[1];
        const char *destination = argv[2];

        
        int source_is_file = !is_file(source);
        int destination_is_file = !is_file(destination);

        
        if (source_is_file && destination_is_file) {
            if (mvRenameFile(source, destination) == 0) {
                printf("File renamed from '%s' to '%s'\n", source, destination);
            } else {
                fprintf(stderr, "Failed to rename file.\n");
            }
        }
        
        else if (!source_is_file && !destination_is_file) {
            if (file_exists(destination)) {
                if (mvMoveDirToDir(source, destination) == 0) {
                    printf("Directory '%s' moved to directory '%s'\n", source, destination);
                } else {
                    fprintf(stderr, "Failed to move directory to directory.\n");
                }
            } else {
                if (mvRenameDir(source, destination) == 0) {
                    printf("Directory renamed from '%s' to '%s'\n", source, destination);
                } else {
                    fprintf(stderr, "Failed to rename directory.\n");
                }
            }

        }
        
        else if (source_is_file && !destination_is_file) {
            if (mvMoveFileToDir(source, destination) == 0) {
                printf("File '%s' moved to directory '%s'\n", source, destination);
            } else {
                fprintf(stderr, "Failed to move file to directory.\n");
            }
        }

        pthread_mutex_destroy(&resource_semaphore);
        return 0; 
    }
}
