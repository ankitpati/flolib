/* flolib.h */
/* Debug-Capable Floating-Point Library Implementation
 *
 * Copyright 2015 Ankit Pati <ankitpati@gmail.com>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the  terms of the GNU Lesser General Public License as published by the  Free
 * Software Foundation; either version 3 of the License, or (at your option) any
 * later version.
 *
 * This  library is distributed in the hope that it will be useful, but  WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You  should  have received a copy of the GNU Lesser  General  Public  License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef apFLOLIB_H
#define apFLOLIB_H

#include <stdint.h>

/* debug section */
#ifdef apFLO_DEBUG

#include <stdio.h>
#include <string.h>

static char *strrev(char *s)
{
    size_t i, j;
    char t;
    for(i=0, j=strlen(s); i<j; ++i){
        t=s[i];
        s[i]=s[--j];
        s[j]=t;
    }
    return s;
}

static void printb(uint64_t d, size_t width)
{
    size_t i = 0;
    char b[(8 * sizeof(d)) + 1];
    do b[i++] = '0' + (d % 2);
    while(d /= 2);
    b[i] = '\0';
    for(i=strlen(b); i < width; ++i) putchar('0');
    printf("%s", strrev(b));
}
#endif
/* end of debug section */

/* IEEE Floating Point Format
+--------+----------+-------------+-------------+
| Symbol | Purpose  | 32-bit Size | 64-bit Size |
+--------+----------+-------------+-------------+
| s      | Sign     | 01          | 01          |
| e      | Exponent | 08          | 11          |
| m      | Mantissa | 23          | 52          |
+--------+----------+-------------+-------------+
*/

/* single-precision code */
enum single_bits{
    SIN_SIGN =  1, SIN_EXPO =  8, SIN_MANT = 23,
};

typedef union{
    float f;
    struct{
        uint32_t m: SIN_MANT;
        uint32_t e: SIN_EXPO;
        uint32_t s: SIN_SIGN;
    } i; /* reverse ordering for little-endian arch (x86) */
} sinflo;

sinflo dec2sin(float f)
{

#ifdef apFLO_DEBUG
    sinflo flo;
    flo.f = f;
    printf("\n%f =", f);
    printf("\nS: "); printb(flo.i.s, SIN_SIGN);
    printf("\nE: "); printb(flo.i.e, SIN_EXPO);
    printf("\nM: "); printb(flo.i.m, SIN_MANT);
    puts("\n");
#endif

    return (sinflo) f;
}

float sin2dec(sinflo flo)
{
    float f;
    f = flo.f;

#ifdef apFLO_DEBUG
    printf("\nS: "); printb(flo.i.s, SIN_SIGN);
    printf("\nE: "); printb(flo.i.e, SIN_EXPO);
    printf("\nM: "); printb(flo.i.m, SIN_MANT);
    printf("\n = %f\n\n", f);
#endif

    return f;
}

sinflo sin_add(sinflo a, sinflo b)
{
    sinflo t;
    int eequal;

    if(a.f == 0.0f) return b;
    else if(b.f == 0.0f) return a; /* zero is special, denormalised */

    if(a.i.e < b.i.e) t = a, a = b, b = t;

    a.i.m >>= 1;
    b.i.m >>= 1; /* shifting to accomodate MSB */

    if(a.i.e != b.i.e) b.i.m |= (1 << (SIN_MANT - 1)); /* inserting MSB */

    b.i.m >>= (a.i.e - b.i.e);
    eequal = (a.i.e == b.i.e);
    b.i.e = a.i.e;

    if(a.i.s == b.i.s){
        b.i.m += a.i.m;
        if((b.i.m >> (SIN_MANT - 1)) && eequal) ++b.i.e;
        else if(b.i.m >> (SIN_MANT - 1) || eequal){
            ++b.i.e;
            b.i.m <<= 1;
            b.i.m >>= 1;
        }
        else b.i.m <<= 1;
    }
    else{
        b.i.s = a.i.s;
        b.i.m = a.i.m - b.i.m;
        if((b.i.m >> (SIN_MANT - 1)) && eequal){
            --b.i.e;
            b.i.m = ~b.i.m + 1;
            b.i.s = !b.i.s;
        }
        else if(b.i.m >> (SIN_MANT - 1) || eequal){
            --b.i.e;
            b.i.m = ~b.i.m + 1;
            b.i.m <<= 1;
            b.i.m >>= 1;
        }
        else b.i.m <<= 1;
    }

    return b;
}

sinflo sin_sub(sinflo a, sinflo b)
{
    b.i.s = !b.i.s;
    return sin_add(a, b);
}
/* end of single-precision code */

/* double-precision code */
enum double_bits{
    DUB_SIGN =  1, DUB_EXPO = 11, DUB_MANT = 52,
};

typedef union{
    double f;
    struct{
        uint64_t m: DUB_MANT;
        uint64_t e: DUB_EXPO;
        uint64_t s: DUB_SIGN;
    } i; /* reverse ordering for little-endian arch (x86) */
} dubflo;

dubflo dec2dub(double f)
{

#ifdef apFLO_DEBUG
    dubflo flo;
    flo.f = f;
    printf("\n%f =", f);
    printf("\nS: "); printb(flo.i.s, DUB_SIGN);
    printf("\nE: "); printb(flo.i.e, DUB_EXPO);
    printf("\nM: "); printb(flo.i.m, DUB_MANT);
    puts("\n");
#endif

    return (dubflo) f;
}

double dub2dec(dubflo flo)
{
    double f;
    f = flo.f;

#ifdef apFLO_DEBUG
    printf("\nS: "); printb(flo.i.s, DUB_SIGN);
    printf("\nE: "); printb(flo.i.e, DUB_EXPO);
    printf("\nM: "); printb(flo.i.m, DUB_MANT);
    printf("\n = %f\n\n", f);
#endif

    return f;
}

dubflo dub_add(dubflo a, dubflo b)
{
    dubflo t;
    int eequal;

    if(a.f == 0.0f) return b;
    else if(b.f == 0.0f) return a; /* zero is special, denormalised */

    if(a.i.e < b.i.e) t = a, a = b, b = t;

    a.i.m >>= 1;
    b.i.m >>= 1; /* shifting to accomodate MSB */

    if(a.i.e != b.i.e) b.i.m |= (1l << (DUB_MANT - 1)); /* inserting MSB */

    b.i.m >>= (a.i.e - b.i.e);
    eequal = (a.i.e == b.i.e);
    b.i.e = a.i.e;

    if(a.i.s == b.i.s){
        b.i.m += a.i.m;
        if((b.i.m >> (DUB_MANT - 1)) && eequal) ++b.i.e;
        else if(b.i.m >> (DUB_MANT - 1) || eequal){
            ++b.i.e;
            b.i.m <<= 1;
            b.i.m >>= 1;
        }
        else b.i.m <<= 1;
    }
    else{
        b.i.s = a.i.s;
        b.i.m = a.i.m - b.i.m;
        if((b.i.m >> (DUB_MANT - 1)) && eequal){
            --b.i.e;
            b.i.m = ~b.i.m + 1;
            b.i.s = !b.i.s;
        }
        else if(b.i.m >> (DUB_MANT - 1) || eequal){
            --b.i.e;
            b.i.m = ~b.i.m + 1;
            b.i.m <<= 1;
            b.i.m >>= 1;
        }
        else b.i.m <<= 1;
    }

    return b;
}

dubflo dub_sub(dubflo a, dubflo b)
{
    b.i.s = !b.i.s;
    return dub_add(a, b);
}
/* end of double-precision code */

#endif
/* end of ifields.h */
