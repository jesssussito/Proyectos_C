#include "conjuntos.h"
#include <stdio.h>

/// Incluir aqui el código de las funciones solicitadas para el TAD Conjunto Disjunto
/// en la representación mediante ÁRBOLES añadiendo la mejora de unión por TAMAÑO. 
/// .........................................................................


//
// Función auxiliar para ver contenido de Partición 
//
void verParticion(particion P)
{ int i;
    printf("\n");
    for (i =0;i<MAX;i++) printf("|%3d",P[i]);
    printf("| contenido  vector\n");
    for (i =0;i<MAX;i++) printf("----");
    printf("\n");
    for (i =0;i<MAX;i++) printf(" %3d",i);
    printf("  índices vector\n\n");
}

// 1. Las tres básicas

void crea(particion P) {
	int i;	
	
	for(i=0;i<MAX;i++) P[i]=-1;
}


tipoConjunto buscar(tipoElementoCon x, particion P) {
	if(P[x] < 0) return x;
	else {
		return buscar(P[x],P);
	}  
}


void unir(tipoConjunto x, tipoConjunto y, particion P) { 
	if(P[x] > P[y]) { // La nueva raiz es y 	
		P[y] = P[x] + P[y];	
		P[x] = y;   	
	}
	else { // La nueva raiz es x 
		P[x] = P[x] + P[y];
		P[y] = x;			
	}
}


// 2. Implementación con control de representantes: Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO, en otro caso no hace nada y devuelve FALSO

int unir1(tipoConjunto x, tipoConjunto y, particion P) {
	if (P[x] > 0 || P[y] > 0) return 0; 
	else {
		if(P[x] > P[y]) { // La nueva raiz es y 
			P[y] = P[x] + P[y];	
			P[x] = y;   	
		}
		else { // La nueva raiz es x 
			P[x] = P[x] + P[y];
			P[y] = x;			
		}
	}
	return 1;
}



// 3. Versión de buscar con Compresión de Caminos

tipoConjunto buscarCC(tipoElementoCon x, particion P) {
	if(P[x] < 0) return x;
	else {
		P[x] = buscarCC(P[x],P);
		return P[x];
	} 
}
