#include "cola.h"
int createTail(list *tail){
    return createVoid(tail);
}
int enqueue(elementType x,list *tail){
    if (tail==NULL)
    {
        return -1;
    }
    typeCell *new = malloc(sizeof(typeCell));
    if (new==NULL)
    {
        return -2;
    }
    new->inf=x;
    new->next=NULL;
    if (tail->last!=NULL)
    {
        tail->last->next=new;
    }
    else{
        tail->root->next=new;
    }
    tail->last=new;
    return 0;  
}
int dequeue(list *tail){
    if (tail->root==NULL || tail ==NULL || tail->root->next==NULL )
    {
        return -1;
    }
    typeCell *temp = tail->root->next;
    tail->root->next = temp->next;
    free(temp);
    if (tail->root->next==NULL)
    {
        tail->last=NULL;
    }
    return 0;
    
}
elementType front(list *tail){
    if (tail == NULL || tail->root == NULL || tail->root->next == NULL) {
        return -1;  
    }
    return tail->root->next->inf;  
}
int isEmptyTail(list *tail){
     if(tail == NULL || tail->root == NULL) {
        return -1; 
    }
    return (tail->root->next == NULL) ? 1 : 0;  // Vacía si no hay nodos
}