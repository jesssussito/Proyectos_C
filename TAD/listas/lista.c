#include "lista.h"
#include <stdlib.h>

int createVoid(list *l){
    typeCell *new;
    new = malloc(sizeof(typeCell));
    if (new!=NULL)
    {
        new->next=NULL;
        l->root = l->last = new;
        return 0;
    }
    return -1; 
}
int annular(list *l){
    typeCell *erase;
    if (l->root!=NULL && l!=NULL)
    {
        while (l->root->next!=NULL)
        {
            erase = l->root->next;
            l->root->next = erase->next;
            free(erase);
        }
        l->last=l->root;
        return 0;
    }
    return -2;
}
int destroy(list *l){
    typeCell *aux;
    if (l==NULL || l->root == NULL)
    {
        return 2;
    }
    while (l->root!=NULL)
    {
        aux=l->root;
        l->root=aux->next;
        free(aux);
    }
    l->last=NULL;
    return 0;
}
int insert(elementType x, typePos p, list *l){
    typeCell *new;
    if (l->root==NULL)
    {
        return -2;
    }
    if (p==NULL)
    {
        return -1;
    }
    new = malloc(sizeof(typeCell));
    if (new!=NULL)
    {
      new->inf=x;
      new->next=p->next;
      p->next=new;
      if (new->next==NULL)
      {
        l->last=new;
      }
      return 0;
    }
    return -1;
}
int supress(typePos p,list *l){
    typeCell *erase;
    if(l==NULL || l->root == NULL)
    {
        return -2;
    }
    if (p==NULL || p->next==NULL)
    {
        return -4;
    }
    erase = p->next;
    p->next=erase->next;
    free(erase);
    if (p->next==NULL)
    {
        l->last=p;
    }
    return 0;
}
typePos first(list *l){
    if(l==NULL || l->root == NULL)
    {
        return NULL;
    }
    return l->root;
}
typePos end(list *l){
    if(l==NULL || l->root == NULL)
    {
        return NULL;
    }
    return l->last;
}
typePos previous(typePos p, list *l){
    typePos aux;
    if(l==NULL ||l->root==NULL){
        return NULL;
    }
    if (p==NULL || p==l->root)
    {
        return NULL;
    }
    aux = l->root;
    while (aux->next!=p)
    {
        aux = aux->next;
    }
    return aux;   
}
typePos next(typePos p, list *l){
    if(l==NULL || l->root == NULL)
    {
        return NULL;
    }
    if (p==NULL)
    {
        return NULL;
    }
    if (p->next!=NULL)
    {
        p=p->next;
    }
    return p;
}
int voidList(list *l){
    if (l->root==NULL)
    {
        return -2;
    }
    if (l->root->next==NULL)
    {
        return 1;
    }
    return 0;   
}

int transferNode(typePos p,typePos q,list *la,list *ll){
    typeCell *aux;
    if (la->root==NULL || ll->root==NULL || la==NULL || ll==NULL)
    {
        return -2;
    }
    if (p==NULL ||q==NULL || p->next ==NULL)
    {
        return -1;
    }
    aux = p->next;
    p->next = aux->next;
    aux->next = q->next;
    q->next=aux;
    if (p->next == NULL)
    {
        la->last=p;
    }
    if (aux->next == NULL)
    {
        ll->last=aux;
    }
    return 0; 
}

void print(list *l){
    typeCell *aux;
    if (l==NULL || l->root == NULL)
    {
        printf("[!] Error\n");
    }
    else{
        aux=l->root->next;
        while (aux!=NULL)
        {
            printf("[%d], ",aux->inf);
            aux=aux->next;
        }
        printf("\n");
    }
}

void printList(list *l){
    elementType inf;
    typePos p;
    p=first(l);
    if (p==NULL)
    {
        printf("[!] Error\n");
    }
    else{
        while (p!=NULL)
        {
            inf=recover(p,l);
            printf("%d",inf);
            p=next(p,l);
        }
        printf("\n");
    }  
}

elementType recoverLast(list *l){
    if(l==NULL || l->root == NULL)
    {
        return -2;
    }
    if (l->root->next==NULL)
    {
        return -4;
    }
    return l->last->inf;
}
elementType recover(typePos p, list *l){
    if(l==NULL || l->root == NULL)
    {
        return -2;
    }
    if (l->root->next==NULL)
    {
        return -4;
    }
    return p->next->inf;
}

typePos locate(elementType x,list *l){
    typePos aux;
    if(l==NULL || l->root == NULL)
    {
        return NULL;
    }
    aux=l->root;
    while (aux->next!=NULL && aux->next->inf!=x)
    {
        aux=aux->next;
    }
    return aux;
}

int splitList(list *l_origin,typePos p,list *l_new){
    if (l_origin==NULL || l_origin->root==NULL)
    {
        return -2;
    }
    if (l_new==NULL)
    {
        return -5;
    }
    if (p==NULL || p->next == NULL)
    {
        return -4;
    }
    if (createVoid(l_new)!=0)
    {
        return -1;
    }
    if (p!=l_origin->last)
    {
        l_new->root->next=p->next;
        l_new->last=l_origin->last;
        p->next=NULL;
        l_origin->last=p;
    }
    return 0; 
}