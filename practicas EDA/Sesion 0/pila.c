#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "pila.h"



int pilaCreaVacia(Pila *p)
{
    *p = NULL;
	return 0;
}

int pilaVacia(Pila *p)
{
    if(*p == NULL) {
		return 1;
	}
	else {
		return 0;
	}
    
}

int pilaInserta(Pila *p,tipoElemento elemento)
{
    Pila aux;

	aux = malloc(sizeof(Pila));
	if (aux == NULL) {
		return -1; 
	}
	else {
		aux->elemento = elemento;
		aux->sig = NULL;
	}
	aux->sig = *p;
	*p = aux;

	return 0;   
}

tipoElemento pilaSuprime(Pila *p)
{
    tipoCelda *aBorrar;
	tipoElemento x;

	if(p == NULL || *p == NULL) {
		return 0;
	}
	else {
		x = (*p)->elemento;
		aBorrar = *p;
		*p = (*p)->sig;
		free(aBorrar);
		return x;
	}
}


