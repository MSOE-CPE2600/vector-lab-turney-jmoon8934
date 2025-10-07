/***************************************************************************
* Filename: 
* Author: Jeric Moon
* Date: 
* Desc: 
****************************************************************************/

#include "vect.h"

myvector vectadd(myvector *a, myvector *b)
{
    myvector result;
    result.x = a->x + b->x;
    result.y = a->y + b->y;
    result.z = a->z + b->z;
    return result;
}

myvector vectorsub(myvector *a, myvector *b)
{
    myvector result;
    result.x = a->x - b->x;
    result.y = a->y - b->y;
    result.z = a->z - b->z;
    return result;
}

myvector scalarmult(myvector *a, float b)
{
    myvector result;
    result.x = a->x*b;
    result.y = a->y*b;
    result.z = a->z*b;
    return result;
}