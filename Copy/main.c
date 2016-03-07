/*
 * File:   main.c
 * Author: logic
 *
 * Created on January 26, 2013, 5:01 PM
 */

#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>
#include "Stack.h"

#define String  char *
#define MIN_ARGS 3

void parse_input(int cli_count, char** cli_options);    // Validate user cli input
void print_usage();                                     // TODO: Print Usage
int is_directory(String path);
String get_basename(String path);
void copy_recursive();

int is_file(String path);
static void list_dir(String src, String dest);

char src_buf[PATH_MAX+1];
char dest_buf[PATH_MAX+1];
String src = src_buf;
String dest = dest_buf;

int main(int argc, char** argv) {
    
    parse_input(argc, argv);
    if (is_directory(src) && is_directory(dest)) {
        //set file creation mask
        umask(S_IWGRP | S_IWOTH);
        strcat(dest, get_basename(src));
        //create new target starting directory
        if (!(mkdir(dest, S_IRWXU | S_IRWXG | S_IRWXO))) {
            printf("Created:\n%s\n\n", dest);
        } else {
            perror("MKDIR");
            exit(EXIT_FAILURE);
        }
        
        copy_recursive();
        
    } else {
        printf("somebody wasnt");
    }
    
    return (EXIT_FAILURE);
}
void parse_input(int cli_c, char** cli_v) {
    
    //only accept two arguments
    if (cli_c == MIN_ARGS) {
        //ensure arguments are valid paths
        if ((realpath(cli_v[1], src))) {
            if ((realpath(cli_v[2], dest))) {
                //remove trailing '/' from path if included
                if (cli_v[1][strlen(cli_v[1])-1] == '/') {
                    cli_v[1][strlen(cli_v[1])-1] = '\0';
                }
                if (cli_v[2][strlen(cli_v[2])-1] == '/') {
                    cli_v[2][strlen(cli_v[2])-1] = '\0';
                }
                strcpy(src, cli_v[1]);
                strcpy(dest, cli_v[2]);
            } else {
                perror("TARGET PATH");
                exit(EXIT_FAILURE);
            }
        } else {
            perror("SOURCE PATH");
            exit(EXIT_FAILURE);
        }
    } else {
        print_usage();
    }
}
void print_usage() {
    printf("PRINT USAGE\n");
    exit(EXIT_FAILURE);
}
int is_directory(String path) {
    
    struct stat file;
    if(!stat(path, &file)) {
        if(S_ISDIR(file.st_mode)) {
            return 1;
        }
    }
    return 0;
}
String get_basename(String path) {
    
    String basename;
    
    if ((basename = strrchr(path, '/'))) {
        return basename;
    }
    
    return NULL;
}
void copy_recursive() {
    
    struct Stack* paths;
    DIR *dir;
    struct dirent *entry;
    const String d_name;
    int dir_count;
    
    dir_count = 0;
    paths = malloc(sizeof (struct Stack));
    s_create(paths);
    s_push(basename(src), paths);
    strcpy(src, dirname(src));
    strcpy(dest, dirname(dest));
    printf("Source: %s\nTarget: %s\n\n", src, dest);

    
    while(!s_isEmpty(paths)) {
        strcat(src, "/");
        strcat(src, s_peek(paths));
        s_pop(paths);
        if((dir = opendir(src))) {
            while((entry = readdir(dir))) {
                d_name = entry->d_name;
                if(entry->d_type & DT_DIR) {
                    printf("Found FOLDER: %s\n", d_name);
                    if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
                        s_push(d_name, paths);
                        dir_count++;
                    }
                } else if (entry->d_type & DT_REG) {
                    printf("Found FILE: %s\n", d_name);
                }
            }
            if (!closedir(dir)) {
                printf("Time to copy\n");
            } else {
                fprintf(stderr, "Could not close '%s': %s\n", src, strerror(errno));
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "Cannot open %s: %s\n", src, strerror(errno));
            exit(EXIT_FAILURE);
        }
        if(dir_count) {
            strcpy(src, dirname(src));
            dir_count--;
        }
    }
}



