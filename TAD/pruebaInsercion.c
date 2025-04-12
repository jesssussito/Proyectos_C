#include "pilas/pila.h"
#include "listas/lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int comparaciones=0;
int movimientos=0;
void insercionDirecta(list *l);
int main(void){
    list lista;
    int n,element;
    srand(time(NULL));
    createVoid(&lista);
    printf("De cuantos elementos quiere la lista:\n");
    scanf("%d",&n);
    for ( int i = 0; i < n; i++)
    {
        element = rand()%100;
        insert(element,lista.root,&lista);
    }
    printf("Lista antes de ordenar:\n");
    print(&lista);
    time_t start_time = time(NULL);
    insercionDirecta(&lista);
    time_t end_time = time(NULL);
    double ejec = (double)(end_time - start_time);
    printf("Lista despues de ordenar:\n");
    print(&lista);  
    printf("El tiempo ha sido de %.12f segundos\n",ejec);
    double ec=(movimientos + comparaciones)* (1.14*pow(10,-8));
    printf("La estimacion teorica de tiempo era %.12f segundos\n",ec);
    printf("A vista parece tardar más, esto es debido a la funcion print\n");
    printf("Aunque los tiempos son tomados solo para la Insercion directa\n");
    destroy(&lista);
    
    
}
void insercionDirecta(list *l){
    if (l==NULL || l->root == NULL || l->root->next==NULL)
    {
        return;
    }
    typePos current =  l->root->next->next;
    typePos prev = l->root;
    typeCell *temp;
    while (current!=NULL)
    {
        temp = current;
        current=current->next;
        typePos pos = l->root;
        while (pos->next!=NULL && pos->next->inf < temp->inf)
        {
            pos = pos->next;
            comparaciones++;
        }
        if (pos->next == temp)
        {
            prev=temp;
            continue;
        }
        prev->next=temp->next;
        movimientos++;
        temp->next=pos->next;
        pos->next=temp;
        movimientos++;
        if (prev->next==NULL)
        {
            l->last=prev;
        }      
    } 
}