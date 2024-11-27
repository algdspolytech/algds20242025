#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

struct point {
    int x;
    int y;
};

struct point makepoint (int x, int y){
    struct point temp;
    temp.x = x;
    temp.y = y;
    return temp;
}

struct point addpoint (struct point p1, struct point p2){
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}

int main(){
    struct point p1, p2, pt, *pp1 = &p1, *pp2 = &p2, *ppt = &pt;
    p1 = makepoint(5, 6);
    p2 = makepoint(5, 4);
    pt = addpoint(p1, p2);
    printf ("%d \t %d", pt.x, pt.y);
    return 0;
}