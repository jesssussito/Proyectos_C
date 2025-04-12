#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conjuntos.h"

/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante LISTAS
/// ......................................................................





void verParticion(particion P)
{ int i;
   tipoCelda *aux;
    for (i =0;i<MAXIMO;i++) {
         aux = P[i].primero;
         if (aux!=NULL)  printf("\n\nClase equivalencia representante %d: ",i);
        while (aux!=NULL)
        { printf("%d ",aux->elemento);
         aux=aux->sig;
        }
    }
}

void verClaseEquivalencia(tipoElemento x,particion P)
{ int representante;
  tipoCelda *aux;
  
    representante = buscar(x,P);
    printf("\n\nClase de Equivalencia de %d cuyo representante es %d: ", x,representante);
    aux = P[representante].primero;
    while (aux)
        { printf(" %d ",aux->elemento);
          aux=aux->sig;
        }
    printf("\n\n");
}




void crea(particion P) {
	int i;	
	tipoCelda *aux;
		
	for (i = 0; i < MAXIMO; i++) {
		aux = (tipoCelda *)malloc(sizeof(tipoCelda));	
		aux->elemento = i;
		aux->sig = NULL;
		P[i].primero = aux;
		P[i].ultimo = aux;
	}
}


tipoConjunto buscar(tipoElemento x, particion P) {
	int i;
	tipoCelda *aux;

    for (i = 0; i < MAXIMO; i++) { // Se recorren todos los elementos del conjunto
        aux = P[i].primero;
        
		while (aux != NULL) { // Se recorre la lista de cada uno de los elmentos del conjunto
			if(aux->elemento == x) return i;
				else aux = aux->sig;
        }
    }
}


void unir(tipoConjunto C1, tipoConjunto C2, particion P) {
	P[C1].ultimo->sig = P[C2].primero; 
	P[C1].ultimo = P[C2].ultimo;
	P[C2].primero = NULL;
	P[C2].ultimo = NULL;
}
