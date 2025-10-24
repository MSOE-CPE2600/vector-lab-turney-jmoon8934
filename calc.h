/***************************************************************************
* Filename: calc.h
* Author: Jeric Moon
* Date: 10/21/2025
* Desc: Header file for calc.c
****************************************************************************/
#ifndef CALC_H
#define CALC_H 

#include "vect.h"

void vectname(myvect *source, char *name);

void vectcopy(myvect *destination, myvect *source);

void vectadd(myvect *result, myvect *source1, myvect *source2);

void vectsub(myvect *result, myvect *source1, myvect *source2);

void scalarmult(myvect *result, myvect *source, float k);

#endif 