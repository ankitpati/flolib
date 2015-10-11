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

#define apFLO_DEBUG

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
    i=strlen(b);
    while(i++ < width) putchar('0');
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
typedef union{
    uint32_t i;
    float    f;
} sinflo;

enum single_bits{
    SIN_SIGN =  1, SIN_EXPO =  8, SIN_MANT = 23,
};

sinflo dec2sin(float f)
{

#ifdef apFLO_DEBUG
    sinflo flo;
    uint32_t shift, s, e, m;

    flo.f = f;
    shift = (8 * sizeof(flo)) - SIN_MANT;
    m = (flo.i << shift) >> shift; /* mantissa */

    flo.i >>= SIN_MANT;
    shift = (8 * sizeof(flo)) - SIN_EXPO;
    e = (flo.i << shift) >> shift; /* exponent */

    flo.i >>= SIN_EXPO;
    shift = (8 * sizeof(flo)) - SIN_SIGN;
    s = (flo.i << shift) >> shift; /* sign */

    printf("\n%.2f =", f);
    printf("\nS: "); printb(s, SIN_SIGN);
    printf("\nE: "); printb(e, SIN_EXPO);
    printf("\nM: "); printb(m, SIN_MANT);
    puts("\n");
#endif

    return (sinflo) f;
}

float sin2dec(sinflo flo)
{

#ifdef apFLO_DEBUG
    float f;
    uint32_t shift, s, e, m;

    f = flo.f;
    shift = (8 * sizeof(flo)) - SIN_MANT;
    m = (flo.i << shift) >> shift; /* mantissa */

    flo.i >>= SIN_MANT;
    shift = (8 * sizeof(flo)) - SIN_EXPO;
    e = (flo.i << shift) >> shift; /* exponent */

    flo.i >>= SIN_EXPO;
    shift = (8 * sizeof(flo)) - SIN_SIGN;
    s = (flo.i << shift) >> shift; /* sign */

    printf("\nS: "); printb(s, SIN_SIGN);
    printf("\nE: "); printb(e, SIN_EXPO);
    printf("\nM: "); printb(m, SIN_MANT);
    printf("\n = %.2f\n\n", f);
#endif

    return f;
}
/* end of single-precision code */

/* double-precision code */
typedef union{
    uint64_t i;
    double   f;
} dubflo;

enum double_bits{
    DUB_SIGN =  1, DUB_EXPO = 11, DUB_MANT = 52,
};

dubflo dec2dub(double f)
{

#ifdef apFLO_DEBUG
    dubflo flo;
    uint64_t shift, s, e, m;

    flo.f = f;
    shift = (8 * sizeof(flo)) - DUB_MANT;
    m = (flo.i << shift) >> shift; /* mantissa */

    flo.i >>= DUB_MANT;
    shift = (8 * sizeof(flo)) - DUB_EXPO;
    e = (flo.i << shift) >> shift; /* exponent */

    flo.i >>= DUB_EXPO;
    shift = (8 * sizeof(flo)) - DUB_SIGN;
    s = (flo.i << shift) >> shift; /* sign */

    printf("\n%.2f =", f);
    printf("\nS: "); printb(s, DUB_SIGN);
    printf("\nE: "); printb(e, DUB_EXPO);
    printf("\nM: "); printb(m, DUB_MANT);
    puts("\n");
#endif

    return (dubflo) f;
}

double dub2dec(dubflo flo)
{

#ifdef apFLO_DEBUG
    double f;
    uint64_t shift, s, e, m;

    f = flo.f;
    shift = (8 * sizeof(flo)) - DUB_MANT;
    m = (flo.i << shift) >> shift; /* mantissa */

    flo.i >>= DUB_MANT;
    shift = (8 * sizeof(flo)) - DUB_EXPO;
    e = (flo.i << shift) >> shift; /* exponent */

    flo.i >>= DUB_EXPO;
    shift = (8 * sizeof(flo)) - DUB_SIGN;
    s = (flo.i << shift) >> shift; /* sign */

    printf("\nS: "); printb(s, DUB_SIGN);
    printf("\nE: "); printb(e, DUB_EXPO);
    printf("\nM: "); printb(m, DUB_MANT);
    printf("\n = %.2f\n\n", f);
#endif

    return f;
}
/* end of double-precision code */

#endif
/* end of ifields.h */
