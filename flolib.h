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

typedef uint32_t sinflo;
typedef uint64_t dubflo;

/* constants */
enum sign{
    PLUS  = 0,
    MINUS = 1
};

/* IEEE Floating Point Format
+--------+----------+-------------+-------------+
| Symbol | Purpose  | 32-bit Size | 64-bit Size |
+--------+----------+-------------+-------------+
| s      | Sign     | 01          | 01          |
| e      | Exponent | 08          | 11          |
| m      | Mantissa | 23          | 52          |
+--------+----------+-------------+-------------+
 */

enum bits{
    sin_sign =  1, sin_mant = 23, sin_expo =  8,
    dub_sign =  1, dub_mant = 52, dub_expo = 11,
};
/* end of constants */

/* debug section */
#ifdef apFLO_DEBUG
#include <stdio.h>
#include <string.h>
#endif

char *strrev(char *s)
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

void printb(dubflo d)
{
    size_t i = 0;
    char b[(8 * sizeof(d)) + 1];
    do b[i++] = '0' + (d % 2);
    while(d /= 2);
    b[i] = '\0';
    printf("%s", strrev(b));
}
/* end of debug section */

sinflo dec2sin(enum sign sn, unsigned long long whole, unsigned long long fract)
{
    sinflo flo, s, e, m, tmp;
    unsigned i;

    if(!whole && !fract) return (sinflo)0; /* denormalised form */

    flo = 0;
    s   = sn;

    for(i = 0, tmp = whole; tmp; tmp >>= 1) ++i;

    flo |= s << ((8 * sizeof(flo)) - sin_sign); /* sign stored */
    return flo;
}
#endif
/* end of ifields.h */
