/***************************************************************************
* Filename: calc.c
* Author: Jeric Moon
* Date: 10/08/2025
* Desc: Handles the calculation methods for vector math.
****************************************************************************/
#include <string.h>

#include "vect.h"

void vectname(myvect *a, char *name)
{
    //Adjusts the name of a vector, if need be.
    strcpy(a->name, name);
}

void vectcopy(myvect *destination, myvect *source)
{
    //Copies vector source values into vector destination
    strcpy(destination->name, source->name);
    destination->x = source->x;
    destination->y = source->y;
    destination->z = source->z;
}

myvect vectadd(myvect *a, myvect *b)
{
    //Adds vect a & b, returns a nameless vector
    myvect result;
    result.x = a->x + b->x;
    result.y = a->y + b->y;
    result.z = a->z + b->z;
    return result;
}

myvect vectsub(myvect *a, myvect *b)
{
    //Subtracts vect b from a, returns a nameless vector
    myvect result;
    result.x = a->x - b->x;
    result.y = a->y - b->y;
    result.z = a->z - b->z;
    return result;
}

myvect scalarmult(myvect*a, float k)
{
    //Applies a scalar mult k to vector a, returns a nameless vector
    myvect result;
    result.x = a->x*k;
    result.y = a->y*k;
    result.z = a->z*k;
    return result;
}