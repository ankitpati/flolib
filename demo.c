#define apFLO_DEBUG

#include <stdio.h>
#include "flolib.h"

int main()
{
    double f;
    dubflo sf;
    printf("Enter a float value:\n");
    scanf(" %lf%*c", &f);
    sf=dec2dub(f);
    f=dub2dec(sf);
    return 0;
}
