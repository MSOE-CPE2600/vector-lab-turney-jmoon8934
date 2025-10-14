/***************************************************************************
* Filename: linkedlist.h
* Author: Jeric Moon
* Date: 10/14/2025
* Desc: Header file which defines linkedlist struct, and linked list f-ns
****************************************************************************/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node
{
    myvect *vect;
    struct node* next;
    struct node* prev;
} node;

typedef struct linked_list
{
    node *head;
    node *tail;
} linked_list;

#endif 