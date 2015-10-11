#define apFLO_DEBUG

#include <stdio.h>
#include "flolib.h"

int main()
{
    float e, f;
    sinflo se, sf;
    printf("Enter 2 float values:\n");
    scanf(" %f %f%*c", &e, &f);
    se=dec2sin(e);
    sf=dec2sin(f);
    se=sin_add(se, sf);
    puts(" =");
    dec2sin(se.f);
    return 0;
}
