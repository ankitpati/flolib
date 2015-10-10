#define apFLO_DEBUG

#include <stdio.h>
#include <stdint.h>
#include "flolib.h"

int main()
{
    union{
        uint32_t i;
        float f;
    } fl;

    fl.f=0.0f;

    printb(fl.i);
    printf("\n%f\n", fl.f);
    return 0;
}
