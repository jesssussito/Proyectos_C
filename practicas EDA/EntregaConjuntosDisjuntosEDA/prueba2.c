#include <stdio.h>
#include <stdlib.h>

#include "conjuntos.h"


int main()
{ particion P;
  int i;


crea(P);
printf("Situación INICIAL: ");
verParticion(P);

// Se forman las siguientes clases de equivalencia haciendo al primer elemento del conjunto su representante:
// {7,0,13,15},{2,3,8,12},{11,1,4,6,14},{9,5,10}

if (unir1(buscar(13,P),buscar(15,P),P) && unir1(buscar(7,P),buscar(0,P),P) && unir1(buscar(7,P),buscar(13,P),P))
	 printf( "Formada clase de equivalencia {7,0,13,15}\n");
else 
	printf(" No puede formarse la clase de equivalencia {7,0,13,15}\n");

if (unir1(buscar(8,P),buscar(12,P),P) && unir1(buscar(3,P),buscar(8,P),P) && unir1(buscar(2,P),buscar(3,P),P)) 
	 printf( "Formada clase de equivalencia {2,3,8,12}\n");
else 
	printf(" No puede formarse la clase de equivalencia {2,3,8,12}\n");


if (unir1(buscar(6,P),buscar(1,P),P) && unir1(buscar(6,P),buscar(4,P),P) && unir1(buscar(11,P),buscar(14,P),P) && unir1(buscar(11,P),buscar(6,P),P))
	 printf( "Formada clase de equivalencia {11,1,4,6,14}\n");
else 
	printf(" No puede formarse la clase de equivalencia {11,1,4,6,14}\n");

if (unir1(buscar(5,P),buscar(10,P),P) && unir1(buscar(9,P),buscar(5,P),P)) 
	 printf( "Formada clase de equivalencia {5,9,10}\n");
else 
	printf(" No puede formarse la clase de equivalencia {5,9,10}\n");

printf("Situación FINAL:   ");

verParticion(P);

printf("\n\nEl elemento 5 pertenence a la clase de equivalencia con representante %d\n",buscar(5,P));

#ifdef LISTAS
verClaseEquivalencia(5,P);
#endif

// ¿Qué operación sería necesaria para relacionar el elemento 12 con el 15?


}
