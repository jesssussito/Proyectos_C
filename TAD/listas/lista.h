#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>

typedef int elementType;
typedef struct typeCell{
    elementType inf;
    struct typeCell *next;
}typeCell;
typedef struct {
    typeCell *root;
    typeCell *last;
}list;
typedef typeCell *typePos;
int createVoid(list *l);
int annular(list *l);
int destroy(list *l);
int insert(elementType x, typePos p, list *l);
int supress(typePos p,list *l);
typePos end(list *l);
typePos first(list *l);
typePos previous(typePos p, list *l);
typePos next(typePos p, list *l);
typePos locate(elementType x, list *l);
int voidList(list *l);
elementType recover(typePos p, list *l);
elementType recoverLast(list *l);
int splitList(list *l_origin, typePos p, list *l_new);
int transferNode(typePos p, typePos q, list *la, list *ll);
void print(list *l);
void printList(list *l);
#endif