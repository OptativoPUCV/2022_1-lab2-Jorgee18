#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
    List *vector = (List*) malloc(sizeof(List));
    vector->head = NULL;
    vector->tail = NULL;
    vector->current = NULL;
    return vector;
}

void * firstList(List * list) 
{
    if(list == NULL) return NULL;
    if(list->head == NULL) return NULL;
    list->current = list->head;

    return list->head->data;
}

void * nextList(List * list) 
{
    if(list == NULL)return NULL;
    if(list->current == NULL) return NULL;
    if(list->current->next == NULL) return NULL;
    list->current = list->current->next;

    return list->current->data;
}

void * lastList(List * list) 
{
    if(list == NULL) return NULL;
    if(list->tail == NULL) return NULL;
    list->current = list->tail;

    return list->tail->data;
}

void * prevList(List * list) {
    if(list == NULL) return NULL;
    if(list->current == NULL)return NULL;
    if(list->current->prev == NULL) return NULL;
    list->current = list->current->prev;

    return list->current->data;
}

void pushFront(List * list, void * data) 
{
    Node *nodoNuevo = createNode(data);
    nodoNuevo->next = list->head;
    if(list == NULL)
    {
        list->head = nodoNuevo;
        list->current = nodoNuevo;
        list->tail = nodoNuevo;
    }
    list->head = nodoNuevo;
    list->current = nodoNuevo;
    list->tail = nodoNuevo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    Node *nodoNuevo = createNode(data);
    list->current->next = nodoNuevo;
    nodoNuevo->prev = list->current;
    if(list->current == list->tail)
        list->tail = nodoNuevo;
   /*Node *nodoNuevo = createNode(data);
   list->current->next = nodoNuevo;
   nodoNuevo->prev = list->current;
   if(list->current->next == NULL)
   {
        list->current->next = nodoNuevo;
   }
   list->current->next = nodoNuevo;
   list->tail = nodoNuevo;
   */

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
    Node* nodoNuevo = createNode(list->current->data);
    
    if(list->current != list->head)
    {
        if(list->current != list->tail)
        {
            list->current->prev->next = list->current->next;
            list->current->next->prev = list->current->prev;
        }
        else
        {
            list->current->prev->next = NULL;
            list->tail = list->current ->prev;
        }
    }
    else
    {
        list->current->next->prev = NULL;
        list->head = list->current->next;
    }
    free(list->current);
    return nodoNuevo->data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}