#ifndef COLA_H
#define COLA_H
#include "../listas/lista.h"
int createTail(list *tail);
int enqueue(elementType x,list *tail);
int dequeue(list *tail);
elementType front(list *tail);
int isEmptyTail(list *tail);
#endif