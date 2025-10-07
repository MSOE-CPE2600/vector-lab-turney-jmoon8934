/***************************************************************************
* Filename: 
* Author: Jeric Moon
* Date: 
* Desc: 
****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "calc.h"
#include "vect.h"
#include "parser.h"

void vectlist(myvector *a, char *output)
{
    sprintf(output, "%-10f %-10f %-10f", a->x, a->y, a->z);
}