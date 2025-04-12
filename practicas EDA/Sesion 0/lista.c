#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "lista.h"



int
creaVacia(Lista *l)
{
    if (l == NULL)
        return -2;
    else if (NULL == (l->raiz = l->ultimo = (tipoCelda *)malloc(sizeof(tipoCelda))))
        return -1;
    else {
        l->raiz->sig = NULL;
        return 0;
    }
}


int
vacia(Lista *l)
{
    if (l == NULL || l->raiz == NULL) {
        return -1;
    }
    else if (l->raiz->sig == NULL)
        return 1;
    else
        return 0;
}

int
destruye(Lista *l)
{
    if (l == NULL || l->raiz == NULL) {
        return -1;
    }
    else if (l->raiz->sig != NULL){
        return -2;
    }
    else {
        free(l->raiz);
        l->raiz = l->ultimo = NULL;
        return 0;
    }
}


void
imprime(Lista *l)
{
    tipoCelda *aImprimir;
    int posicion;
    
    if (l == NULL || l->raiz == NULL) {
        return;
    }
    else {
        posicion = 1;
        aImprimir = l->raiz->sig;
        while (aImprimir != NULL) {
            printf("Valor: %d en posición: %d\n",aImprimir->elemento, posicion++);
            aImprimir = aImprimir->sig;
        }
        printf("%d valores en la lista\n",posicion-1);
    }
}

tipoPosicion
anterior(tipoPosicion p, Lista *l)
{
    tipoCelda *anterior;
    
    if (l == NULL || l->raiz == NULL || p == NULL) {
        return NULL;
    }
    else if (p == l->raiz){
        return l->raiz;
    }
    else {
        anterior = l->raiz;
        while (anterior->sig != p)
            anterior = anterior->sig;
        return anterior;
    }
}


tipoPosicion
primero(Lista *l)
{
   	if (l == NULL || l->raiz == NULL) {
		return NULL;
   	}
	return l->raiz;	
}



tipoPosicion
fin(Lista *l)
{
    if (l == NULL || l->raiz == NULL || l->ultimo == NULL) {
		return NULL;	
	}	
	return l->ultimo;
}


int
inserta(tipoElemento x, tipoPosicion p, Lista *l)
{
    tipoPosicion aux;
	if (l == NULL || l->raiz == NULL || p == NULL || l->ultimo == NULL) { 
		return -2;	
	}
	else {
		aux = (tipoCelda *)malloc(sizeof(tipoCelda));
		if (aux == NULL) {
			return -1; 
		}
	   	else {
			aux->elemento = x;
			aux->sig = NULL;
    	}
		aux->sig = p->sig;
		p->sig = aux;

		if(p == l->ultimo){
			l->ultimo = aux;
		}
	}
}


int
suprime (tipoPosicion p, Lista *l)
{
    tipoPosicion aBorrar;
	
	if (l == NULL || l->raiz == NULL || p == NULL || l->ultimo == NULL) { 
		return -2;	
	}
	else {
		aBorrar = p->sig;
		p->sig = aBorrar->sig;
		if(aBorrar == l->ultimo)
			l->ultimo = p;

		free(aBorrar);
	}
	return 0;
}



tipoPosicion
siguiente(tipoPosicion p,Lista *l)
{
	tipoPosicion q;

    if (l == NULL || l->raiz == NULL || p == NULL || l->ultimo == NULL) { 
		return NULL;	
	}
	else if (p == l->ultimo) {
		return l->ultimo;
		}
		else {
			return p->sig;
	}
}




tipoPosicion
localiza (tipoElemento x, Lista *l)
{
	tipoPosicion q;
	if (l == NULL || l->raiz == NULL || l->ultimo == NULL) { 
		return NULL;	
	}
	else {
		q = l->raiz;
			
		while (q->sig != NULL) {
			if (q->sig->elemento = x) {
				return q;		
			}
		q = q->sig;
		} 
		return q;
	}
}



tipoElemento
recupera(tipoPosicion p, Lista *l)
{
    tipoPosicion q;

    if (l == NULL || l->raiz == NULL || p == NULL || l->ultimo == NULL) { 
		return -2;	
	}
	else if (p == l->ultimo) {
		return l->ultimo->elemento;
		}
		else {
			return p->sig->elemento;
	}
}


int
anula(Lista *l)
{
    tipoPosicion q, aBorrar;
	
	if (l == NULL || l->raiz == NULL || l->ultimo == NULL) {
		return -2;	
	}		
	else {
		q = l->raiz;
		
		while(q->sig != NULL) {
			aBorrar = q->sig;
			q->sig = aBorrar->sig;
			free(aBorrar);
		}
		l->ultimo = q;
		return 0;	
	}
}

int
concatena(Lista *lA, Lista *lB)
{
	tipoPosicion q;	
	
    if (lA == NULL || lB== NULL) {
		return -2;
	}
	else {
		lA->ultimo->sig = lB->raiz->sig;
		lA->ultimo = lB->ultimo;
	
		lB->ultimo = lB->raiz;
		lB->raiz->sig = NULL;

		return 0;
	}
}


int 
traspasarNodo(tipoPosicion p, Lista *la, tipoPosicion q, Lista *lb) {
	if (lA == NULL || lB== NULL || p == NULL) {
		return -2;
	}
	else {
		inserta(recupera(p,la),q,lb);
		suprime(p,la);
		return 0;
	}
}
