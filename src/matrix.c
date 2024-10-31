#include "matrix.h"

#define START 100
#define ILENGTH 100
#include <stdbool.h>


#define for_elems(f, s) for(int i = 0; i < f; ++i) for(int j = 0; j < s; ++j)

static void extend(void** arr, unsigned int capacity)
{
    *arr = realloc(*arr, sizeof(*arr) * capacity);
}


static int calc_end(const char* str)
{
    int end = 0;
    while (str[end] != ',' && str[end] != '}') ++end;
    return end;
}


static void to_buffer(const char* str, char* buff, int* index)
{
    int end = calc_end(str + *index) + *index;
    memcpy(buff, str + *index, end - *index);
    buff[end - *index] = '\0';
    *index = end;
}


static void to_table(const char* buff, int** table, int i, int j)
{
    char* g = NULL;
    table[i][j] = strtod(buff, &g);
}


static void extend_rows(int*** table, unsigned int* capacity, unsigned int cols)
{
    *capacity *= 2;
    extend(table, *capacity);
    for (int t = *capacity / 2; t < *capacity; ++t) (*table)[t] = malloc(sizeof(int) * cols);
}


static void extend_cols(int** table, unsigned int* cols, unsigned int rows)
{
    *cols *= 2;
    for (int t = 0; t < rows; ++t) extend(&table[t], &cols);
}

static void to_matrix(matrix* mat, int** table)
{
    for_elems(mat->height, mat->width) mat->elems[i][j] = table[i][j];
}


static void delete_table(int** table, unsigned int height)
{
    for (int i = 0; i < height; ++i)
    {
        free(table[i]);
    }
    free(table);
}

matrix* Create(unsigned int height, unsigned int width)
{
    matrix* ma = (matrix*)malloc(sizeof(matrix));
    ma->elems = (double**)malloc(sizeof(double*) * height);
    ma->height = height;
    ma->width = width;
    for (unsigned int i = 0; i < height; ++i)
    {
        ma->elems[i] = (double*)malloc(sizeof(double) * width);
    }
    return ma;
}

matrix* Parse(const char* str)
{
    matrix* res;
    int** nums = malloc(sizeof(int*) * START);
    for (int i = 0; i < START; ++i) nums[i] = malloc(sizeof(int) * START);
    int rows = START, cols = START;
    int index = 0, i = 0, j = 0, end = 0, width, height;
    while (true)
    {
        if (str[index] == '{') index += 1;
        else if (str[index] == '}')
        {
            i += 1;
            height = i;
            j = 0;
            if (i == rows)
            {
                extend_rows(&nums, &rows, cols);
            }
            if (str[index + 1] == '}') break;
            index += 1;
        }
        else if (str[index] == ',') index += 2;
        else
        {
            if (j == cols)
            {
                extend_cols(nums, &cols, rows);
            }
            char* buffer[ILENGTH];
            to_buffer(str, buffer, &index);
            to_table(buffer, nums, i, j);
            j++;
            width = j;
        }
    }
    res = Create(height, width);
    to_matrix(res, nums);
    delete_table(nums, height);
    return res;
}

static void extend_str(char* str, unsigned int* size)
{
    *size *= 2;
    str = realloc(str, size);
}


char* ReadFile(const char* filename)
{
    FILE *fptr;
    errno_t err = fopen_s(&fptr, filename, 'rw');
    if(err == 0) return NULL;
    char* buffer[START];
    char* res = malloc(START);
    unsigned int size = 0;
    unsigned int capacity = START;
    while(fgets(buffer, START, &fptr))
    {
        if(capacity - size <= START) extend_str(res, &capacity);
        strcat(res, buffer);
        size += START;
    }
    fclose(&fptr);
    return res;
}