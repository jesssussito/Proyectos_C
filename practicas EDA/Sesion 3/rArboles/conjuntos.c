#include "conjuntos.h"
#include <stdio.h>


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



/// Incluir aqui las funciones que implementan las tres operaciones básicas 
/// en la representación de CONJUNTOS DISJUNTOS mediante ÁRBOLES
/// ......................................................................

void crea(particion P) {
	int i;	
	
	for(i=0;i<MAXIMO;i++) P[i]=i;
}


tipoConjunto buscar(tipoElemento x, particion P) {
	return P[x];
}


void unir(tipoConjunto x, tipoConjunto y, particion P) {
	int i;
		
	for(i=0;i<MAXIMO;i++) {
		// Si el elemento i es el segundo tipoConjunto que es le pasa y ademas no tiene padre, x sera entonces su nuevo padre
		if(P[i] == y && P[i] == i) P[i] = x; 
			else P[y] = x; 
	}
}



