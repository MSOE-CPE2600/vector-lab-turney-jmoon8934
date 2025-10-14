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

void vect_values(myvect a, char *output)
{
    //Formats a vector's values for printing
    sprintf(output, "%-10f %-10f %-10f", a.x, a.y, a.z);
}

int vect_name_contains(char *name, myvect *list, int array_size)
{
    //Checks to see if a given vector array contains a vector with the passed in name.
    int pos = -1;
    bool found = false;
    for(int i = 0; i < array_size && !found; i++)
    {
            if(!strcmp(list[i].name, name))
        {
            found = true;
            pos = i;
        }

    }
    return pos;
}