#include "xor.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Russian");
    Node* l = NULL;
    l = add(l, "alpha\0");
    l = add(l, "beta\0");
    l = add(l, "gamma\0");
    it(l); 
    Node* f = find(l, "beta\0");
    if (f != NULL) {
      printf("Найдено: %s\n", f->data); 
    }
    l = dbk(l, "beta\0");
    it(l); 

    found = find(l, "beta\0");
    if (f == NULL) {
      printf("Не найдена: Бета\n"); 
    }
    l = dn(l, l);
    it(l); 
    return 0;
}
