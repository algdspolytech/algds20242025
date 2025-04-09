#include <stdio.h>
#include <stdlib.h>
#include "printtree.h"

#define max(x,y) (((x) >= (y)) ? (x) : (y))



node* createnode(int x, node* left, node* right) {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->left = left;
    newnode->right = right;
    newnode->x = x;
    return newnode;
}

void freetree(node* node) {
    if (node == NULL) 
        return;
    freetree(node->left);
    freetree(node->right);
    free(node);
}

node* readtreerec(int* array, int index, int len) {
    if (index >= len)
        return NULL;
    return createnode(array[index], readtreerec(array, 2 * index + 1, len), readtreerec(array, 2 * index + 2, len));
}

node* readtree(FILE* FILE) {
    int len = 0;
    int size = 2;
    int* array = (int*)malloc(sizeof(int) * size);
    int temp = 0;
    while (fscanf(FILE, "%i", &temp) != EOF) {
        if (len >= size) {
            size *= 2;
            array = (int*)realloc(array, sizeof(int) * size);
        }
        array[len] = temp;
        len++;
    }
    array = (int*)realloc(array, len * sizeof(int));
    return readtreerec(array, 0, len);
}

int getdepth(node* node) {
    if (node == NULL)
        return 0;
    return 1 + max(getdepth(node->left), getdepth(node->right));
}

void fprinttab(FILE* out, int n) {
    for (int i = 0;i < n;i++)
        fprintf(out, " ");
}


void displaytree1(FILE* out, node* tree) {
    const int symbolwidth = 4;
    int depth = getdepth(tree);
    int currentlength = 1;       
    int nextsize = 2;            
    int nextlength = 0;          
    node** currentline = (node**)malloc(sizeof(node*));
    node** nextline = (node**)malloc(sizeof(node*) * nextsize); 
    currentline[0] = tree; 
    int totalWidth = (int) (pow(2, depth)) * (symbolwidth + 1) + 1;
    for (int i = 0; i < depth; i++) {
        int items = currentlength; 
        int tab = (int) (totalWidth - symbolwidth * items) / (int)(pow(2, i + 1));
        for (int j = 0; j < currentlength; j++) {
            fprinttab(out, tab);
            if (j > 0)
                fprinttab(out, tab);
            if (currentline[j])
                fprintf(out, "%4i", currentline[j]->x);
        }
        fprinttab(out, tab);
        fprintf(out, "\n");
        for (int j = 0; j < currentlength; j++) {
            if (nextlength + 2 >= nextsize) {
                nextsize *= 2;
                nextline = (node**)realloc(nextline, sizeof(node*) * nextsize);
            }
            if (currentline[j]) {
                nextline[nextlength] = currentline[j]->left;
                nextline[nextlength + 1] = currentline[j]->right;
            }
            nextlength += 2;
        }
        currentline = (node**)realloc(currentline, sizeof(node*) * nextsize);
        for (int i = 0; i < nextlength; i++)
            currentline[i] = nextline[i];
        currentlength = nextlength;
        nextlength = 0;
    }
    free(nextline);
    free(currentline);
}

void displaytree2(FILE* out, node* node) {
    if (node == NULL) 
        return;
    fprintf(out, "%i ", node->x);
    displaytree2(out, node->left);
    displaytree2(out, node->right);
}

void displayfile(FILE* FILE) {
    char line[256];
    if (FILE != NULL) {
        while (fgets(line, sizeof(line), FILE))
            printf("%s", line);
        fclose(FILE);
    }
}
