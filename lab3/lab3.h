#ifndef LAB3_H
#define LAB3_H
void get_data(char *name, int *B, int *N, int **A);
int find_subset(int *nums, int num, int B, int *res, int pointer);
void print_to_file(char *name, int *res);
int *main_program(char *input, char *output);
#endif