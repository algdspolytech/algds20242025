#include "funcs.h"
#include <locale.h>
#include <stdio.h>

int main() {

  Node *Schedule = read_file("test.txt");
  print_filtered_list(Schedule, 8);
  free_all(&Schedule);

  return 0;
}
