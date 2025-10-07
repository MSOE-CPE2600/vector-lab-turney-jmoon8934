/***************************************************************************
* Filename: 
* Author: Jeric Moon
* Date: 
* Desc: 
* Note: 
****************************************************************************/

#include <stdio.h>

#include "calc.h"
#include "vect.h"
#include "parser.h"

int main(void)
{
    myvector a;
    a.x = 1;
    a.y = 2;
    a.z = 3;

    myvector b;
    b.x = 1;
    b.y = 2;
    b.z = 3;

    myvector c = vectadd(&a, &b);
    char vectc[50];
    vectlist(&c, vectc);
    printf("%s\n", vectc);
    return 0;
}

