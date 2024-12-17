#include <stdio.h>
#include <stdbool.h>

typedef struct Node{
    int x;
    int y;
}Node;

Node * addPoint(Node * p1, Node * p2){
    p1->x += p2->x;
    p1->y += p2->y;
    return p1;
}

int main(){
    Node p, *p1 = &p;
    p1->x = 1;
    p1->y = 2;
    Node o, *p2 = &o;
    p2->x = 3;
    p2->y = 4;
    printf("%d\n", addPoint(p1, p2)->y);
    printf("%d\n", p1->y);
    return 0;
}