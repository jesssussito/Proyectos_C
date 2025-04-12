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
	
	for(i=0;i<MAXIMO;i++) P[i] = -1;  // en el enunciado pone que altura inicial -1
}


tipoConjunto buscar(tipoElemento x, particion P) {
	if(P[x] <= 0) return x;
	else {
		P[x] = buscar(P[x],P);
		return P[x];
	} 
}


void unir(tipoConjunto x, tipoConjunto y, particion P) { // Alomejor se podria hacer una comprobacion de errores para que P[x] y P[y] sean siempre < 0 ya que tienen que ser raices y siempre seran negativas
	int i;
		
	if(P[x] > P[y]) { //la nueva raiz es y 	//tiene que ser mayor ya que -1 > -2
		P[x] = y;   
	}
	else { //la nueva raiz es x  //entra aqui en caso de que x sea menor y en caso de que tengan el mismo tamaño (enunciado)
		if(P[y] = P[x]) P[x] = P[x] - 1; //Si los dos arboles tienen la misma altura , la altura del arbol sera h1 + 1
		P[y] = x;	
	}
}



