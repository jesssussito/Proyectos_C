#include "ejercicio1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
   El criterio seguido para las claves repetidas es que no se permite mas de un nodo con la misma clave, 
   sino que se ira almacenando el numero de veces que se ha intentado insertar dicho registro en el campo
   info del nodo.
*/

int genABB(char *ficheroDatos, tipoArbolBB *arbol) {
	FILE *f;
	tipoAlumno alumno;
	int aux = 0, contador = 0, contador2 = 0;

	f = fopen(ficheroDatos,"rb");
	rewind(f);
	fread(&alumno,sizeof(alumno),1,f);
    
	while (!feof(f)) {		

		contador = insertar(arbol, alumno.ape1);
		contador2 = insertar(arbol, alumno.ape2);
		
		if (contador == -1 || contador2 == -1) return -1;
		
		aux = aux + contador + contador2;

		fread(&alumno,sizeof(alumno),1,f);

	}
	
	fclose(f);
	return aux;
}

int insertar(tipoArbolBB *arbol, tipoClave alumno) { 
	tipoNodo *nuevo;

  	if (*arbol == NULL) {
  		if ((nuevo = (tipoNodo *)malloc(sizeof(tipoNodo))) == NULL)
		return -1;
	  	else {
			strcpy(nuevo->clave, alumno);
			nuevo->info = 1;
			nuevo->izq=NULL;
	  		nuevo->der=NULL; 
	    }
		(*arbol) = nuevo;
		return 1;
	} else if (strcmp(alumno, (*arbol)->clave) == 0) {
		(*arbol)->info = (*arbol)->info + 1;
		return 0;
  	} else if (strcmp(alumno, (*arbol)->clave) < 0) {
        insertar(&((*arbol)->izq), alumno);
	} else if (strcmp(alumno, (*arbol)->clave) > 0) {
		insertar(&((*arbol)->der), alumno);
	}
}



void enOrden(tipoArbolBB a) {
 if (a != NULL) { 
	enOrden(a->izq);
	if (a->info > 1) {
		printf("%s\t\tVeces insertado:%d \n", a->clave,a->info);
	}
    enOrden(a->der);
  }
} 
