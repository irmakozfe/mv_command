#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include "/Users/buseokcu/CLionProjects/mv_command/include/flags.h"

void display_help() {
    printf("Usage: mv [OPTION]... SOURCE DEST\n");
    printf("  --backup[=CONTROL]       make a backup of each existing destination file\n");
    printf("  -b                       like --backup but does not accept an argument\n");
    printf("  -f, --force              do not prompt before overwriting\n");
    printf("  -i, --interactive        prompt before overwrite\n");
    printf("  -n, --no-clobber         do not overwrite an existing file\n");
    printf("  --strip-trailing-slashes remove any trailing slashes from each SOURCE argument\n");
    printf("  -S, --suffix=SUFFIX      override the usual backup suffix\n");
    printf("  -t, --target-directory   move all SOURCE arguments into DIRECTORY\n");
    printf("  -T, --no-target-directory treat DEST as a normal file\n");
    printf("  -u, --update             move only when SOURCE file is newer than the destination file\n");
    printf("  -v, --verbose            explain what is being done\n");
    printf("  -Z, --context            set SELinux security context of destination file\n");
    printf("  --help                   display this help and exit\n");
    printf("  --version                output version information and exit\n");
    exit(0);
}

void display_version() {
    printf("mv (custom implementation) 1.0\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    int opt;
    int force = 0, interactive = 0, no_clobber = 0, verbose = 0, update = 0;
    char *backup_suffix = "~";
    char *target_directory = NULL;

    struct option long_options[] = {
        {"backup", optional_argument, NULL, 'B'},
        {"force", no_argument, NULL, 'f'},
        {"interactive", no_argument, NULL, 'i'},
        {"no-clobber", no_argument, NULL, 'n'},
        {"strip-trailing-slashes", no_argument, NULL, 's'},
        {"suffix", required_argument, NULL, 'S'},
        {"target-directory", required_argument, NULL, 't'},
        {"no-target-directory", no_argument, NULL, 'T'},
        {"update", no_argument, NULL, 'u'},
        {"verbose", no_argument, NULL, 'v'},
        {"context", no_argument, NULL, 'Z'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'V'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "bfinS:t:TuZvh", long_options, NULL)) != -1) {
        switch (opt) {
            case 'B':
                if (optarg) {
                    printf("Backup control: %s\n", optarg);
                } else {
                    printf("Backup enabled with default control\n");
                }
                break;
            case 'b':
                printf("Backup enabled\n");
                break;
            case 'f':
                force = 1;
                break;
            case 'i':
                interactive = 1;
                break;
            case 'n':
                no_clobber = 1;
                break;
            case 'S':
                backup_suffix = optarg;
                break;
            case 't':
                target_directory = optarg;
                break;
            case 'T':
                printf("Treat DEST as a normal file\n");
                break;
            case 'u':
                update = 1;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'Z':
                printf("Set SELinux context\n");
                break;
            case 'h':
                display_help();
                break;
            case 'V':
                display_version();
                break;
            case '?':
                fprintf(stderr, "Unknown option: %c\n", optopt);
                exit(1);
        }
    }

    if (verbose) {
        printf("Force: %d, Interactive: %d, No Clobber: %d, Update: %d\n", force, interactive, no_clobber, update);
    }

    // Further implementation for moving files would go here

    return 0;
}
