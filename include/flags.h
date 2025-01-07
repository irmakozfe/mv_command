#ifndef FLAGS_H
#define FLAGS_H

#include <getopt.h>

// Global değişkenler
extern int force;
extern int interactive;
extern int no_clobber;
extern int verbose;
extern int update;
extern char *backup_suffix;
extern char *target_directory;

// İşlev prototipleri
void display_help();
void display_version();
void process_flags(int argc, char *argv[]);

#endif // FLAGS_H
