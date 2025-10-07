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

    myvector c = vectsub(&a, &b);
    myvector d = vectadd(&a, &b);
    char vecta[50];
    char vectb[50];
    char vectc[50];
    char vectb[50];
    vectlist(&a, vectb);
    vectlist(&b, vectb);
    vectlist(&c, vectc);
    vectlist(&d, vectd);
    printf("Vector a's value is %s\n", vecta);
    printf("Vector b's value is %s\n", vectb);
    printf("Vector c = a-b\n");
    printf("Vector c's value is %s", vectc);
    printf("Vector d = a+b\n");
    printf("Vector d's value is %s", vectc);


    return 0;
}

