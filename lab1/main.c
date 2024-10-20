#include <stdio.h>
#include <locale.h>
#include "funcs.h"


int main() {

    Node* Schedule = read_file("test.txt");
    print_list(&Schedule);
    free(Schedule);
    
    return 0;
}
