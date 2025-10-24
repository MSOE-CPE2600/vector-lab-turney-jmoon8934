/***************************************************************************
* Filename: parser.h
* Author: Jeric Moon
* Date: 10/09/2025
* Desc: Header file for parser.c
****************************************************************************/
#ifndef PARSER_H
#define PARSER_H 

#include "vect.h"
#include "linkedlist.h"

void vect_values(myvect *a, char *output);

myvect *vect_name_contains(char *name, linked_list *list);

void listVectors(linked_list *my_list);

void printVector(myvect *a);
#endif 