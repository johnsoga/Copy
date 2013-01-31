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
#include "Stack.h"


#define N_ITEMS 1
#define BYTE_LENGTH 1
#define String  char *


int copy_recursive(String src, char*dest);
int is_folder(String path);
int is_file(String path);
int create_basedir(String src, String dest);
static void list_dir(String src, String dest);

int main(int argc, char** argv) {
    
    
    String src = malloc(strlen(argv[1]) + 1);
    String dest = malloc(strlen(argv[2]) + 1);
    
    char buf[PATH_MAX];
    String temp;
    
    
    if ((src != NULL) && (dest != NULL)) {
        strcpy(src, argv[1]);
        strcpy(dest, argv[2]);
        
        if ((temp = realpath(src, buf)) != NULL) {
            strcpy(src, buf);
            if ((temp = realpath(dest, buf)) != NULL) {
                strcpy(dest, buf);
                copy_recursive(src, dest);
            } else {
                perror("INVALID PATH: ");
            }
        } else {
            perror("INVALID PATH: ");
        }
    } else {
        perror("MALLOC: ");
    }
    
    
    
    /*
     FILE *fp1 = NULL;
     FILE *fp2 = NULL;
     long buf[N_ITEMS];
     char string[256];
     
     String path1 = "/Users/logic/Desktop/src/";
     String path2 = "/Users/logic/Desktop/dest/";
     String extension = ".txt";
     size_t items_read;
     long count = 0;
     long size = 12704331;
     int i = 0;
     long j = 0;
     
     
     for(i = 1; i < 6; i++) {
     
     snprintf(string, sizeof string, "%s%i%s", path1, i, extension);
     printf("%s\n", string);
     fp1 = fopen(string, "r");
     snprintf(string, sizeof string, "%s%i%s", path2, i, extension);
     printf("%s\n", string);
     fp2 = fopen(string, "a");
     
     if(fp1 != NULL) {printf("file 1 opened\n");} else {printf("file 1 failed: %d\n", errno);}
     if(fp2 != NULL) {printf("file 2 opened\n");} else {printf("file 2 failed: %d\n", errno);}
     
     while((items_read = fread(buf, BYTE_LENGTH, N_ITEMS, fp1)) != 0) {
     fwrite(buf, BYTE_LENGTH, N_ITEMS, fp2);
     }
     
     
     
     printf("%ld\n", count);
     printf("%ld bytes off\n", (size-count));
     
     
     fclose(fp1);
     fclose(fp2);
     }
     */
    return (EXIT_SUCCESS);
}

/*
 * If there is a trailing backlash in src then create a directory in dest that
 * is the has the same name as the last directory of src
 *
 * i.e.
 *
 *  if source is defined as
 *      source=/path/to/src/dir/
 *  then basedir /dir/ should be created in dest
 *      dest=/path/to/dest/dir/
 *
 *  all files will be placed under /dir/ in dest
 *
 */
int create_basedir(String src, String dest) {
    
    unsigned long s_length = strlen(src)+1;
    int result;
    String d_basedir;
    
    if (!(src[s_length - 1] == '/')) {
        if ((d_basedir = strrchr(src, '/')) != NULL) {
            printf("%zul: %s\n", strlen(dest), dest);
            printf("%zd: %s\n", strlen(d_basedir), dest);
            printf("dest: %zd\nbase: %zd\ntogether: %ld\n", strlen(dest), strlen(d_basedir), strlen(dest) + strlen(d_basedir));
            dest = realloc(dest, strlen(dest) + strlen(d_basedir) + 1);
            printf("%zd: %s\n", strlen(dest), dest);
            if (dest != NULL) {
                strcat(dest, d_basedir);
                umask(S_IWGRP | S_IWOTH);
                if ((result = mkdir(dest, S_IRWXU | S_IRWXG | S_IRWXO)) == 0) {
                    /*
                     * TODO: make attributes i.e permissions, timestamps match
                     *       original if command line flag is set
                     */
                } else {
                    printf("%d\n", result);
                    perror("mkdir");
                    return -1;
                }
            } else {
                perror("REALLOC: ");
                return -1;
            }
        } else {
            fprintf(stderr, "INVALID FORMAT: source directory");
            return -1;
        }
    }
    
    printf("%c\n", src[s_length-2]);
    return 0;
}

int is_file(String path) {
    
    struct stat file;
    
    if (stat(path, &file) == 0) {
        if (file.st_mode & S_IFREG) return 1;
        else return 0;
    }
    
    return -1;
}

int is_folder(String path) {
    
    struct stat file;
    
    if (stat(path, &file) == 0) {
        if (file.st_mode & S_IFDIR) return 1;
        else return 0;
    }
    return -1;
}


//TODO: NEED TO BE FINISHED

int copy_recursive(String src, String dest) {
    
    DIR *directory;
    struct dirent file;
    
    if (create_basedir(src, dest) == 0) {
        
        list_dir(src, dest);
    }
    
    return 0;
}

void list_dir(String src, String dest) {
    
    struct Stack* files = NULL;
    DIR * dir;
    struct dirent * entry;
    const String d_name;
    String tmp;
    
    dir = opendir(src);
    files = malloc(sizeof (struct Stack));
    
    
    if ((dir != NULL) && (files != NULL)) {
        while ((entry = readdir(dir)) != NULL) {
            
            d_name = entry->d_name;
            
            if (entry->d_type & DT_DIR) {
                printf("Found FOLDER: %s\n", d_name);
                if (strcmp(d_name, "..") != 0 && strcmp(d_name, ".") != 0) {
                    tmp = malloc(strlen(src) + strlen(d_name) + 2);
                    strcpy(tmp, src);
                    strcat(tmp, "/");
                    strcat(tmp, d_name);
                    
                    list_dir(tmp,dest);
                }
            } else if (entry->d_type & DT_REG) {
                printf("Found FILE: %s/%s\n", src, d_name);
            }
        }
        
        if (!closedir(dir)) {
            
            printf("Time to copy\n");
            return;
        } else {
            fprintf(stderr, "Could not close '%s': %s\n", src, strerror(errno));
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Cannot open %s: %s\n",
                src, strerror(errno));
        exit(EXIT_FAILURE);
    }
}