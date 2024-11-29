#include <stdio.h>
#include <stdlib.h>
#include "A_v29.h"

#define MAX_PATHS 500
#define MAX_P_LEN 255
#define MAX_NAME 8

dir* create_dir(const char* name, int len) {
    dir* d = (dir*)malloc(sizeof(dir));
    for (int i = 0; i < len && i < MAX_NAME; i++) {
        d->name[i] = name[i];
    }
    d->name[len] = '\0';
    d->subdir_cnt = 0;
    return d;
}

dir* find_subdir(dir* fldr, const char* name, int len) {
    for (int i = 0; i < fldr->subdir_cnt; i++) {
        int flag = 1;
        for (int j = 0; j < len; j++) {
            if (fldr->subdirs[i]->name[j] != name[j]) {
                flag = 0;
                break;
            }
        }
        if (flag && fldr->subdirs[i]->name[len] == '\0') {
            return fldr->subdirs[i];
        }
    }
    return NULL;
}

void add_subdir(dir* fldr, dir* subdir) {
    fldr->subdirs[fldr->subdir_cnt++] = subdir;
}

int sort_dirs(const void* a, const void* b) {
    dir* dirA = *(dir**)a;
    dir* dirB = *(dir**)b;

    int i = 0;
    while (dirA->name[i] != '\0' && dirB->name[i] != '\0') {
        if (dirA->name[i] < dirB->name[i]) {
            return -1;
        }

        if (dirA->name[i] > dirB->name[i]) {
            return 1;
        }
        i++;
    }

    if (dirA->name[i] == '\0' && dirB->name[i] != '\0') {
        return -1;
    }
    if (dirA->name[i] != '\0' && dirB->name[i] == '\0') {
        return 1;
    }
    return 0;
}

void print_tree(FILE* output, dir* d, int tier) {
    qsort(d->subdirs, d->subdir_cnt, sizeof(dir*), sort_dirs);
    if (d->name[0] != '\0') {
        for (int i = 0; i < tier; i++) {
            fprintf(output, " ");
        }

        for (int i = 0; d->name[i] != '\0'; i++) {
            fprintf(output, "%c", d->name[i]);
        }
        fprintf(output, "\n");
    }
    for (int i = 0; i < d->subdir_cnt; i++) {
        print_tree(output, d->subdirs[i], tier + 1);
    }
}

dir* read_tree_from_file(const char* filename) {
    FILE* input;
    fopen_s(&input, filename, "r");
    if (!input) {
        printf("Error: unable to open input file\n");
        return NULL;
    }

    int n;
    fscanf_s(input, "%i", &n);

    dir* loc = create_dir("", 0);
    char current_name[MAX_NAME + 1];
    int current_len = 0;
    dir* current = loc;

    int c;
    while ((c = fgetc(input)) != EOF) {
        if (c == '\\' || c == '\n') {
            if (current_len > 0) {
                dir* subdir = find_subdir(current, current_name, current_len);
                if (!subdir) {
                    subdir = create_dir(current_name, current_len);
                    add_subdir(current, subdir);
                }
                current = subdir;
                current_len = 0;
            }
            if (c == '\n') {
                current = loc;
            }
        }
        else {
            if (current_len < MAX_NAME) {
                current_name[current_len++] = c;
            }
        }
    }

    if (current_len > 0) {
        dir* subdir = find_subdir(current, current_name, current_len);
        if (!subdir) {
            subdir = create_dir(current_name, current_len);
            add_subdir(current, subdir);
        }
    }

    fclose(input);
    return loc;
}

void write_tree_to_file(const char* filename, dir* root) {
    FILE* output;
    fopen_s(&output, filename, "w");
    if (!output) {
        printf("Error: unable to open output file\n");
        return;
    }

    qsort(root->subdirs, root->subdir_cnt, sizeof(dir*), sort_dirs);

    for (int i = 0; i < root->subdir_cnt; i++) {
        print_tree(output, root->subdirs[i], 0);
    }

    fclose(output);
}
