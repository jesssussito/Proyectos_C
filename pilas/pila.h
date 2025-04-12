#ifndef pile_H
#define pile_H
#include "../listas/lista.h" 
int createpile(list *pile);
int push(elementType x, list *pile);
int pop(list *pile);
elementType top(list *pile);
int isEmptypile(list *pile);

#endif
