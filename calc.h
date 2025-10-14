/***************************************************************************
* Filename: calc.h
* Author: Jeric Moon
* Date: 10/08/2025
* Desc: Header file for calc.c
****************************************************************************/
#ifndef CALC_H
#define CALC_H 

#include "vect.h"

void vectname(myvect *a, char *name);

void vectcopy(myvect *destination, myvect *source);

myvect vectadd(myvect *a, myvect *b);

myvect vectsub(myvect *a, myvect *b);

myvect scalarmult(myvect *a, float k);

#endif 