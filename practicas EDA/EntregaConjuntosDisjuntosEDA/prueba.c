#include <stdio.h>
#include <stdlib.h>

#include "conjuntos.h"


int main()
{ particion P;
  int i;


crea(P);
printf("Situaci�n INICIAL: ");
verParticion(P);

// Se forman las siguientes clases de equivalencia haciendo al primer elemento del conjunto su representante:
// {7,0,13,15},{2,3,8,12},{11,1,4,6,14},{9,5,10}

// � Cuidado ! Es necesario utilizar la funci�n buscar para obtener resultados correctos
unir(buscar(13,P),buscar(15,P),P);
unir(buscar(7,P),buscar(0,P),P);
unir(buscar(7,P),buscar(13,P),P);

unir(buscar(8,P),buscar(12,P),P);		
unir(buscar(3,P),buscar(8,P),P);		
unir(buscar(2,P),buscar(3,P),P);  		

unir(buscar(6,P),buscar(1,P),P);		
unir(buscar(6,P),buscar(4,P),P);		
unir(buscar(11,P),buscar(14,P),P);	
unir(buscar(11,P),buscar(6,P),P);	

unir(buscar(5,P),buscar(10,P),P);		
unir(buscar(9,P),buscar(5,P),P);		
printf("Situaci�n FINAL:   ");

verParticion(P);

printf("\n\nEl elemento 5 pertenence a la clase de equivalencia con representante %d\n",buscar(5,P));

#ifdef LISTAS
verClaseEquivalencia(5,P);
#endif

// �Qu� operaci�n ser�a necesaria para relacionar el elemento 12 con el 15?


}
