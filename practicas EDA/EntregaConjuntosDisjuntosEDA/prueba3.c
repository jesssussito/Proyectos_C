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
// {5,1,7,8,9,13},{11,3,4,14,15},{2,6,12,10,0}

if (unir1(buscarCC(5,P),buscarCC(1,P),P) && unir1(buscarCC(5,P),buscarCC(7,P),P) && unir1(buscarCC(1,P),buscarCC(8,P),P) && unir1(buscarCC(1,P),buscarCC(9,P),P) && unir1(buscarCC(7,P),buscarCC(13,P),P))
	 printf("Formada clase de equivalencia {5,1,7,8,9,13}\n");
else 
	printf(" No puede formarse la clase de equivalencia {5,1,7,8,9,13}\n");

if (unir1(buscarCC(11,P),buscarCC(3,P),P) && unir1(buscarCC(11,P),buscarCC(4,P),P) && unir1(buscarCC(3,P),buscarCC(14,P),P) && unir1(buscarCC(3,P),buscarCC(15,P),P)) 
	 printf("Formada clase de equivalencia {11,3,4,14,15}\n");
else 
	printf(" No puede formarse la clase de equivalencia {11,3,4,14,15}\n");

if (unir1(buscarCC(2,P),buscarCC(6,P),P) && unir1(buscarCC(2,P),buscarCC(12,P),P) && unir1(buscarCC(6,P),buscarCC(10,P),P) && unir1(buscarCC(6,P),buscarCC(0,P),P))
	 printf("Formada clase de equivalencia {2,6,12,10,0}\n");
else 
	printf(" No puede formarse la clase de equivalencia {2,6,12,10,0}\n");


printf("Situación FINAL:   ");

verParticion(P);

printf("\n\nEl elemento 5 pertenence a la clase de equivalencia con representante %d\n",buscarCC(5,P));

#ifdef LISTAS
verClaseEquivalencia(5,P);
#endif

// ¿Qué operación sería necesaria para relacionar el elemento 12 con el 15?


}
