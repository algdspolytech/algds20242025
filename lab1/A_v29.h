#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MAX_PATHS 500
#define MAX_P_LEN 255
#define MAX_NAME 8

typedef struct dir {
    char name[MAX_NAME + 1];
    struct dir* subdirs[MAX_PATHS];
    int subdir_cnt;
} dir;

dir* create_dir(const char* name, int len);
dir* find_subdir(dir* fldr, const char* name, int len);
void add_subdir(dir* fldr, dir* subdir);
int sort_dirs(const void* a, const void* b);
void print_tree(FILE* output, dir* d, int tier);
dir* read_tree_from_file(const char* filename);  
void write_tree_to_file(const char* filename, dir* root);
