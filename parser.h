/***************************************************************************
* Filename: parser.h
* Author: Jeric Moon
* Date: 10/09/2025
* Desc: Header file for parser.c
****************************************************************************/
#ifndef PARSER_H
#define PARSER_H 

#include "vect.h"

void vect_values(myvect a, char *output);

int vect_name_contains(char *name, myvect *list, int array_size);

#endif 