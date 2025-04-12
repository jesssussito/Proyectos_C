#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../listas/lista.h"
//estoy en pile.c
int createpile(list *pile){
    return createVoid(pile);
}
int push(elementType x, list *pile){
    if (pile==NULL)
    {
        return -1;
    }
    typeCell *new = malloc(sizeof(typeCell));
    if (new==NULL)
    {
        return -2;
    }
    new->inf=x;
    new->next=pile->root->next;
    pile->root->next=new;
    if (new->next==NULL)
    {
        pile->last=new;
    }
    return 0;   
}
int pop(list *pile){
if (pile == NULL || pile->root == NULL || pile->root->next == NULL) {
        return -1;  // Error: pile vacía o no inicializada
    }

    typeCell *temp = pile->root->next;  // Nodo a eliminar
    pile->root->next = temp->next;     // Actualizar el enlace
    free(temp);                        // Liberar memoria

    if (pile->root->next == NULL) {
        pile->last = pile->root;  // Actualizar el último nodo si la pile queda vacía
    }
    return 0;  // Éxito
}

elementType top(list *pile) {
    if (pile == NULL || pile->root == NULL || pile->root->next == NULL) {
        return -1;  // Error: pile vacía o no inicializada
    }
    return pile->root->next->inf;  // Retornar el valor del primer nodo
}

int isEmptypile(list *pile) {
    if (pile == NULL || pile->root == NULL) {
        return -1;  // Error: pile no inicializada
    }
    return (pile->root->next == NULL) ? 1 : 0;  // Vacía si no hay nodos
}




