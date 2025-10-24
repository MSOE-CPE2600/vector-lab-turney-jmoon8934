/***************************************************************************
* Filename: calc.c
* Author: Jeric Moon
* Date: 10/08/2025
* Desc: Handles the calculation methods for vector math.
****************************************************************************/
#include <string.h>

#include "vect.h"

void vectname(myvect *source, char *name)
{
    //Adjusts the name of a vector, if need be.
    strcpy(source->name, name);
}


void vectcopy(myvect *destination, myvect *source)
{
    //Copies vector source values into vector destination
    strcpy(destination->name, source->name);
    destination->x = source->x;
    destination->y = source->y;
    destination->z = source->z;
}

void vectadd(myvect *result, myvect *source1, myvect *source2)
{
    //Adds vect a & b, returns a nameless vector
    result->x = source1->x + source2->x;
    result->y = source1->y + source2->y;
    result->z = source1->z + source2->z;
}

void vectsub(myvect *result, myvect *source1, myvect *source2)
{
    //Subtracts vect b from a, returns a nameless vector
    result->x = source1->x - source2->x;
    result->y = source1->y - source2->y;
    result->z = source1->z - source2->z;
}

void scalarmult(myvect *result, myvect *source, float k)
{
    //Applies a scalar mult k to vector source, update values of vector result
    result->x = source->x*k;
    result->y = source->y*k;
    result->z = source->z*k;
}