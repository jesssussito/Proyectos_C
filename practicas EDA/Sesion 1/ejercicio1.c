#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

int main(void)
{ Arbol varArbol,varArbol2;
  Arbol nodoMax,nodoMin;

/* Creación arbol ejemplo de las transparencias de recorridos */
  varArbol = creaNodo('A');
  varArbol->izq=creaNodo('B');
  varArbol->der = creaNodo('C');
  varArbol->izq->izq=creaNodo('D');
  varArbol->izq->der=creaNodo('E');
  varArbol->der->izq=creaNodo('F');
  varArbol->der->der=creaNodo('G');

/* Creación del segundo arbol ejemplo de las transparencias de recorridos */
  varArbol2 = creaNodo('A');
  varArbol2->izq=creaNodo('B');
  varArbol2->der = creaNodo('C');
  varArbol2->izq->izq=creaNodo('D');
  varArbol2->izq->der=creaNodo('E');
  varArbol2->der->izq=creaNodo('F');
  varArbol2->der->der=creaNodo('G');


  /*varArbol2 = creaNodo('A');
  varArbol2->der=creaNodo('B');
  varArbol2->izq = creaNodo('C');
  varArbol2->der->der=creaNodo('D');
  varArbol2->der->izq=creaNodo('E');
  varArbol2->izq->der=creaNodo('F');
  varArbol2->izq->izq=creaNodo('G');*/

/* Aplicación de recorridos al arbol ejemplo */

  printf("Recorrido en PRE_ORDEN: ");
  preOrden(varArbol);
  printf("\n");
  printf("Recorrido en ORDEN: ");
  enOrden(varArbol);
  printf("\n");
  printf("Recorrido en POST_ORDEN: ");
  postOrden(varArbol);
  printf("\n");
  printf("Recorrido en AMPLITUD: ");
  amplitud(varArbol);
  printf("\n");

/* Comenzar a implementar y probar las funciones del ejercicio 2 ... y segunda parte del ejercicio 3 */


/* EJERCICIO 2 */

	printf("La altura del arbol binario es %d \n", altura(varArbol));	
	printf("El arbol binario tiene %d nodos\n", numNodos(varArbol));

	//anula(varArbol);	
	//printf("El arbol binario tiene %d nodos\n", numNodos(varArbol));
	//preOrden(varArbol);

	//printf("Se han realizado %d sustituciones\n", sustituye(varArbol, 'B', 'S'));
	//amplitud(varArbol);

	printf("El arbol binario tiene %d nodos hojas\n", numNodosHoja(varArbol));
	printf("El arbol binario tiene %d nodos internos\n", numNodosInternos(varArbol));
	printf("El arbol binario tiene %d nodos unicos\n", numHijoUnico(varArbol));

	nodoMax = buscarMax(varArbol);
	printf("El maximo nodo del arbol binario es %c \n", nodoMax->info);

	nodoMin = buscarMin(varArbol);
	printf("El minimo nodo del arbol binario es %c \n", nodoMin->info);

	if(similares(varArbol,varArbol2)) 
		printf("El arbol binario es similar\n");
	else 
		printf("El arbol binario no es similar\n");


	if(equivalentes(varArbol,varArbol2)) 
		printf("El arbol binario es equivalente\n");
	else 
		printf("El arbol binario no es equivalente\n");


  return 1;
}

