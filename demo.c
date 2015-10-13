#define apFLO_DEBUG

#include <stdio.h>
#include "flolib.h"

int main()
{
    int    ch , pr;
    float  e0 , f0;
    double e1 , f1;
    sinflo le0, lf0;
    dubflo le1, lf1;

    for(;;){
        puts("What would you like to do?");
        puts(" (0) Exit");
        puts(" (1) Display a float");
        puts(" (2) Add two floats");
        puts(" (3) Subtract two floats");
        scanf(" %d%*c", &ch);
        if(!ch) return 0;
        puts("Choose precision:");
        puts(" (0) Single");
        puts(" (1) Double");
        scanf(" %d%*c", &pr);
        switch(ch){
        case 1:
            puts("Enter a float:");
            if(!pr){
                scanf(" %f%*c", &e0);
                dec2sin(e0);
            }
            else{
                scanf(" %lf%*c", &e1);
                dec2dub(e1);
            }
            break;

        case 2:
            puts("Enter two floats:");
            if(!pr){
                scanf(" %f %f%*c", &e0, &f0);
                le0 = dec2sin(e0);
                lf0 = dec2sin(f0);
                sin2dec(sin_add(le0, lf0));
            }
            else{
                scanf(" %lf %lf%*c", &e1, &f1);
                le1 = dec2dub(e1);
                lf1 = dec2dub(f1);
                dub2dec(dub_add(le1, lf1));
            }
            break;

        case 3:
            puts("Enter two floats:");
            if(!pr){
                scanf(" %f %f%*c", &e0, &f0);
                le0 = dec2sin(e0);
                lf0 = dec2sin(f0);
                sin2dec(sin_sub(le0, lf0));
            }
            else{
                scanf(" %lf %lf%*c", &e1, &f1);
                le1 = dec2dub(e1);
                lf1 = dec2dub(f1);
                dub2dec(dub_sub(le1, lf1));
            }
            break;
        }
    }

    return 0;
}
