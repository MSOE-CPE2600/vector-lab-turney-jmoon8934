/***************************************************************************
* Filename: parser.c
* Author: Jeric Moon
* Date: 10/08/2025
* Desc: Helper file that contains helper functions to make data parsing easier.
****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "calc.h"
#include "vect.h"
#include "parser.h"
#include "linkedlist.h"

void vect_values(myvect *a, char *output)
{
    //Formats a vector's values for printing
    sprintf(output, "%-10f %-10f %-10f", a->x, a->y, a->z);
}

myvect *vect_name_contains(char *name, linked_list *list)
{
    node *curr = list->head;
    while(curr)
    {
        //Explicitly check if they're equal by comparing result to 0.
        if(strcmp(curr->vect->name, name) == 0)
        {
            return curr->vect;
        }
        else
        {
            curr = curr->next;
        }
    }
    return NULL;
}

void listVectors(linked_list *my_list)
{
    node *curr = my_list->head;
    while(curr)
    {
        char myvect_printout[50];
        vect_values(curr->vect, myvect_printout);
        printf("Value of vector: %s is %s\n", curr->vect->name, myvect_printout);
        curr = curr->next;
    }
}

void printVector(myvect *a)
{
    char myvect_printout[50];
    vect_values(a, myvect_printout);
    printf("Value of vector: %s is %s\n", a->name, myvect_printout);
}