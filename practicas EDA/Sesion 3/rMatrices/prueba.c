#include <stdio.h>
#include <stdlib.h>

#include "conjuntos.h"

int main()
{ particion P;
  int i;


crea(P);
printf("Situación INICIAL: ");
verParticion(P);

// Se forman las siguientes clases de equivalencia haciendo al primer elemento del conjunto su representatne:
// {7,0,13,15},{2,3,8,12},{11,1,4,6,14},{9,5,10}


unir(13,15,P);		// Mejor unir(buscar(13,P),buscar(15,P),P);
unir(7,0,P);		// Mejor unir(buscar(7,P),buscar(0,P),P);
unir(7,13,P);		// Mejor unir(buscar(7,P),buscar(13,P),P);

unir(8,12,P);		// Mejor ...
unir(3,8,P);		// Mejor ...
unir(2,3,P);		// Mejor ...

unir(6,1,P);		// Mejor ...
unir(6,4,P);		// Mejor ...
unir(11,14,P);		// Mejor ...
unir(11,6,P);		// Mejor ...

unir(5,10,P);		// Mejor ...
unir(9,5,P);		// Mejor ...

printf("Situación FINAL:   ");

verParticion(P);

printf("\n\nEl elemento 5 pertenence a la clase de equivalencia con representante %d\n",buscar(5,P));


// ¿Qué operación sería necesaria para relacionar el elemento 12 con el 15?


}
