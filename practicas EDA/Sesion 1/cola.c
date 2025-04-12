#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "cola.h"



int colaCreaVacia(Cola *c)
{
    if(c == NULL) {
		return -2;
	}
	else {
		c->frente = NULL;
		c->fondo = NULL;
		return 0;
	}     
}

int colaVacia(Cola *c)
{
    if(c == NULL) {
		return -1;
	} else if(c->frente == NULL || c->fondo == NULL) 
			return 1; 
		else 
			return 0;
    
}

int colaInserta(Cola *c,tipoElemento elemento)
{
    tipoCelda *aux;

	if(c == NULL){
		return -2;
	}
	else {
		aux = malloc(sizeof(tipoCelda *));
		if (aux == NULL) {
			return -1; 
		}
		else {
			aux->elemento = elemento;
			aux->sig = NULL;
		}
		
		if(c->fondo == NULL) {
			c->fondo = aux;
			c->frente = aux;
			return 0;
		}
		else {
			c->fondo->sig = aux;
			c->fondo = aux;
			return 0;
		}
	}	
}


tipoElemento colaSuprime(Cola *c)
{
    tipoCelda *aBorrar;
	tipoElemento x;

	if(c == NULL || c->frente == NULL) {
		return NULL;
	}
	else {
		x = c->frente->elemento;
		aBorrar = c->frente;
		c->frente = c->frente->sig;
		free(aBorrar);

		if(c->frente == NULL) {
			c->fondo = NULL;
		}

		return x;
	}
    
}
