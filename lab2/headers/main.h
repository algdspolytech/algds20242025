#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/list.h"
#include "../headers/matrix.h"
#include "../headers/queue.h"

#ifdef __cplusplus

extern "C" {
#endif

char CompareGraphs(const char *filepath_to_list,
                   const char *filepath_to_matrix);

#ifdef __cplusplus
}
#endif