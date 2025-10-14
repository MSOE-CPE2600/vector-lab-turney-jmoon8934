/***************************************************************************
* Filename: linkedlist.c
* Author: Jeric Moon
* Date: 10/14/2025
* Desc: Provides method functionalities for a linked list implementation
****************************************************************************/
#include <stdlib.h>

#include "vect.h"
#include "linkedlist.h"

static node *makeNode(myvect *vector)
{
    node *new_node = malloc(sizeof(node));
    new_node->vect = malloc(sizeof(myvect));
    new_node->vect = vector;
    return new_node;
}

static void killNode(node *to_kill)
{
    free(to_kill->vect);
    free(to_kill);
    return;
}

linked_list llInit(void)
{
    linked_list return_list = {NULL, NULL};
    return return_list;
}

int llSize(linked_list *my_list)
{
    int size = 0;
    node *iterator = my_list->head;
    while(iterator)
    {
        size++;
        iterator = iterator->next;
    }
    return size;
}

int llPushToFront(linked_list *my_list, myvect *to_store)
{
    if(to_store)
    {
        node *new_node = makeNode(to_store);

        if(my_list->head == NULL)
        {
            my_list->head = my_list->tail = new_node;
        }
        else
        {
            new_node->next = my_list->head;
            my_list->head->prev = new_node;
            my_list->head = new_node;
        }
        return 0;
    }
    return -1;
}

int llPushBack(linked_list *my_list, myvect *to_store)
{
        if(to_store)
    {
        node *new_node = makeNode(to_store);

        if(my_list->head == NULL)
        {
            my_list->head = my_list->tail = new_node;
        }
        else
        {
            my_list->tail->next = new_node;
            new_node->next = NULL;
            my_list->tail = new_node;
        }
        return 0;
    }
    return -1;
}

int llInstertAfter(linked_list *my_list, node *insert_node, myvect *to_store)
{
    int to_return = 0;
    if(to_store && insert_node)
    {
        if(insert_node == my_list->tail)
        {
            to_return = llPushBack(my_list, to_store);
        }
        else
        {
            node *new_node = makeNode(to_store);

            insert_node->next->prev = new_node;
            new_node->next = insert_node->next;
            new_node->prev = insert_node;
            insert_node->next = new_node;

            if(insert_node == my_list->tail)
            {
                my_list->tail = new_node;
            }
        }
        return to_return;
    }
    return -1;
}

int llRemove(linked_list *my_list, node *rmv_node)
{
    if(rmv_node)
    {
        if(rmv_node->next)
        {
            rmv_node->next->prev = rmv_node->prev;
        }
        else
        {
            my_list->tail = rmv_node->prev;
        }
        if(rmv_node->prev)
        {
            rmv_node->prev->next = rmv_node->next;
        }
        else
        {
            my_list->head = rmv_node->next;
        }
        killNode(rmv_node);
        return 0;
    }
    return -1;
}

void llClear(linked_list *my_list)
{
    while(!llRemove(my_list, my_list->head))
    {
    }
    return;
}