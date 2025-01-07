#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

// Flag değişkenleri
int force = 0;
int interactive = 0;
int no_clobber = 0;
int verbose = 0;
int update = 0;

// Yardım mesajını görüntüle
void display_help() {
    printf("Usage: mv [options] source destination\n");
    printf("Options:\n");
    printf("  -f, --force         Force move without confirmation\n");
    printf("  -i, --interactive   Prompt before overwrite\n");
    printf("  -n, --no-clobber    Do not overwrite an existing file\n");
    printf("  -u, --update        Move only when the source is newer\n");
    printf("  -v, --verbose       Explain what is being done\n");
    printf("  -h, --help          Display this help and exit\n");
    printf("  -V, --version       Display version information\n");
}

// Sürüm bilgisi göster
void display_version() {
    printf("mv command version 1.0\n");
}

// Flags'i işle
void process_flags(int argc, char *argv[]) {
    int opt;
    struct option long_options[] = {
        {"force", no_argument, NULL, 'f'},
        {"interactive", no_argument, NULL, 'i'},
        {"no-clobber", no_argument, NULL, 'n'},
        {"update", no_argument, NULL, 'u'},
        {"verbose", no_argument, NULL, 'v'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'V'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "finuvh", long_options, NULL)) != -1) {
        switch (opt) {
            case 'f':
                force = 1;
                break;
            case 'i':
                interactive = 1;
                break;
            case 'n':
                no_clobber = 1;
                break;
            case 'u':
                update = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'h':
                display_help();
                exit(0);
            case 'V':
                display_version();
                exit(0);
            case '?':
                fprintf(stderr, "Unknown option: %c\n", optopt);
                exit(1);
        }
    }
