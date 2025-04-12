#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbolBB.h"

int main(void)
{ tipoArbolBB a=NULL;
  tipoNodo *buscado;
  int encontrado;

 insertar(&a,25);
 insertar(&a,35);
 insertar(&a,15);
 insertar(&a,20);
 insertar(&a,12);
 insertar(&a,13);
 insertar(&a,15);
 insertar(&a,15);
 insertar(&a,15);
 insertar(&a,45);
 insertar(&a,30);
 insertar(&a,10);
 printf("Secuencia de los nodos en orden: \n");
 enOrden(a);
 encontrado = buscar(15,a, &buscado); 
 if (encontrado)
	printf("\nEncontrado nodo con clave %d e información %d \n", buscado->clave,buscado->info);
 else  printf("No existe nodo o error (%d) \n", encontrado);

 encontrado = buscar(100,a, &buscado); 
 if (encontrado)
	printf("\nEncontrado nodo con clave %d e información %d \n", buscado->clave,buscado->info);
 else  printf("No existe nodo o error(%d) \n", encontrado);


// ESTO LO HE AÑADIDO YO
 printf("\n\nEliminados %d nodos con clave %d\n", eliminar(&a,5),5);
 printf("Eliminados %d nodos con clave %d\n", eliminar(&a,15),15);
 printf("Eliminados %d nodos con clave %d\n", eliminar(&a,35),35);
 printf("Secuencia de los nodos en orden: \n");
 enOrden(a);
 return 1;
}


