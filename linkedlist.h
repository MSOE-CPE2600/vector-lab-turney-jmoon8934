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

linked_list llInit(void);

int llSize(linked_list *my_list);

int llPushToFront(linked_list *my_list, myvect *to_store);

int llPushBack(linked_list *my_list, myvect *to_store);

int llInstertAfter(linked_list *my_list, node *insert_node, myvect *to_store);

int llRemove(linked_list *my_list, node *rmv_node);

void llClear(linked_list *my_list);

#endif 