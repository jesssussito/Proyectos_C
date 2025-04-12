#include "conjuntos.h"
#include <stdio.h>
/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante MATRICES
/// ......................................................................




//
// Función auxiliar para ver contenido de Partición 
//
void verParticion(particion P)
{ int i;
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf("|%2d",P[i]);
    printf("| contenido  vector\n");
    for (i =0;i<MAXIMO;i++) printf("---");
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf(" %2d",i);
    printf("  índices vector\n\n");
}



void crea(particion P) {
	int i;	
	
	for(i=0;i<MAXIMO;i++) P[i]=i;
}


tipoConjunto buscar(tipoElemento x, particion P) { // Devuelve el valor que contiene el elmento x, es decir, el representante del conjunto
	return P[x];
}


void unir(tipoConjunto x, tipoConjunto y, particion P) {
	int i;
		
	for(i=0;i<MAXIMO;i++) { // Se recorre toda la matriz cambiando las clases de eq	uivalencia que contengan y por x
		if(P[i] == y) P[i] = x; 
	}
}

