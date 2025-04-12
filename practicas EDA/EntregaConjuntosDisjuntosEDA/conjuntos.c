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
    for (i =0;i<MAXIMO;i++) printf("|%3d",P[i]);
    printf("| contenido  vector\n");
    for (i =0;i<MAXIMO;i++) printf("----");
    printf("\n");
    for (i =0;i<MAXIMO;i++) printf(" %3d",i);
    printf("  índices vector\n\n");
}

// 1. Las tres básicas

void crea(particion P) {
	int i;	
	
	for(i=0;i<MAXIMO;i++) P[i]=-1;
}


tipoConjunto buscar(tipoElemento x, particion P) {
	if(P[x] < 0) return x;
	else {
		return buscar(P[x],P); // Busqueda recursiva , por ejemplo si el elemento contiene 5, la siguiente busqueda sera al contenido del elemento 5 y asi hasta que llegue a la raiz
	}  
}


void unir(tipoConjunto x, tipoConjunto y, particion P) { 
	// Si por ejemplo P[x] = -1 y P[y] = -2 
	if(P[x] > P[y]) { // La nueva raiz es y 	
		P[y] = P[x] + P[y];	// El tama�o de y (la raiz) sera su tama�o mas el de x (-1-2 = -3)
		P[x] = y; // x ahora contiene a su padre, es decir, y  	
	}
	else { // La nueva raiz es x 
		P[x] = P[x] + P[y]; // El tama�o de x (la raiz) sera su tama�o mas el de y
		P[y] = x; // y ahora contiene a su padre, es decir, x			
	}
}


// 2. Implementación con control de representantes: Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO, en otro caso no hace nada y devuelve FALSO

int unir1(tipoConjunto x, tipoConjunto y, particion P) {
	if (P[x] > 0 || P[y] > 0) return 0; // Si el contenido de alguno de los argumentos es un numero mayor que 0 significa que tienen padre, por lo que no seran raiz y se devuelve Falso
	else { // Union normal como la de arriba
		if(P[x] > P[y]) { // La nueva raiz es y 
			P[y] = P[x] + P[y];	
			P[x] = y;   	
		}
		else { // La nueva raiz es x 
			P[x] = P[x] + P[y];
			P[y] = x;			
		}
	}
	return 1; // Se devuelve verdadero
}



// 3. Versión de buscar con Compresión de Caminos

// Todo nodo padre que se encuentre x a su paso se unira directamente a la raiz
tipoConjunto buscarCC(tipoElemento x, particion P) {
	if(P[x] < 0) return x; // P[x] es raiz al contener un numero negativo
	else {
		P[x] = buscarCC(P[x],P); // Busqueda recursiva , por ejemplo si el elemento contiene 5, la siguiente busqueda sera al contenido del elemento 5 y asi hasta que llegue a la raiz
		return P[x];
	} 
}
