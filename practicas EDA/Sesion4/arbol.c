#include <stdlib.h>
#include <stdio.h>
#include "arbol.h"
#include "cola.h"

//
// Reserva de memoria para un nuevo nodo de árbol binario
//
Arbol creaNodo(tipoInfo info)
{ tipoNodo * nuevo;

  //   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL)
	return NULL;
  else
  { 	nuevo->info=info;
	nuevo->izq=NULL;
	nuevo->der=NULL;
	return nuevo;
   }
}

//
// Recorrido en amplitud o por niveles: necesita una cola de punteros a nodos de árbol binario!!!
//

void amplitud(Arbol raiz)
{ Cola c;
  tipoNodo *nodo;
  colaCreaVacia(&c);
  nodo = raiz;
  if (raiz!=NULL) colaInserta(&c,nodo);
  while (!colaVacia(&c))
  { nodo = (Arbol) colaSuprime(&c);
    printf(" %c ", nodo->info);
    if (nodo->izq!=NULL) colaInserta(&c,nodo->izq);
    if (nodo->der!=NULL) colaInserta(&c,nodo->der);
  }
}
// 
// Recorridos en profundidad "recursivos"
//
void preOrden(Arbol raiz)
{ if (raiz!=NULL)
  { printf("%c ",raiz->info);
    preOrden(raiz->izq);
    preOrden(raiz->der);
  }
}
void enOrden(Arbol raiz)
{ if (raiz!=NULL)
  { enOrden(raiz->izq);
    printf("%c ",raiz->info);
    enOrden(raiz->der);
  }
}
void postOrden(Arbol raiz)
{ if (raiz!=NULL)
  { postOrden(raiz->izq);
    postOrden(raiz->der);
    printf("%c ",raiz->info);
  }
}



// 
// Funciones Ejercicio 2
//

int altura(Arbol raiz) {
	int alt_izq, alt_der;
	
	if(raiz == NULL) {
		return -1;
	} else {
		alt_izq = altura(raiz->izq);
		alt_der = altura(raiz->der);
	
		if(alt_izq > alt_der) {
			return alt_izq + 1;
		} else {
			return alt_der + 1;
		}
	}

}


int numNodos(Arbol raiz) {
	int izq, der;

	if(raiz == NULL) {
		return 0;
	} else {
		izq = numNodos(raiz->izq);
		der = numNodos(raiz->der);
		
		return izq + der + 1; 
	}
	
}


Arbol anula(Arbol raiz) {
	if(raiz == NULL) {
		return NULL;
	} else {
		raiz->izq = anula(raiz->izq);
		raiz->der = anula(raiz->der);
		free(raiz);

		return NULL; 
	}

}


int sustituye(Arbol raiz, tipoInfo x, tipoInfo y) {
	int sus_izq, sus_der;		
	
	if(raiz == NULL) {
		return 0;
	} else {
		sus_izq = sustituye(raiz, x, y);
		sus_der = sustituye(raiz, x, y);
		
		if (raiz->info == x) {
			raiz->info = y;
			return sus_izq + sus_der +1;
		}
		
		return sus_izq + sus_der;
	}
}


int numNodosHoja(Arbol raiz) {
	int hoja_izq, hoja_der;	

	if(raiz == NULL) {
		return 0;
	} else {
   		hoja_izq = numNodosHoja(raiz->izq);
		hoja_der = numNodosHoja(raiz->der);

		if(raiz->izq == NULL && raiz->der == NULL) {
			return hoja_izq + hoja_der + 1;
		}
		return hoja_izq + hoja_der;
    }

}


int numNodosInternos(Arbol raiz) {
	int int_izq, int_der;	

	if(raiz == NULL) {
		return 0;
	} else {
   		int_izq = numNodosInternos(raiz->izq);
		int_der = numNodosInternos(raiz->der);

		if(raiz->izq != NULL || raiz->der != NULL) {
			return int_izq + int_der + 1;
		}
		return int_izq + int_der;
    }
}


int numHijoUnico(Arbol raiz) {
	int unico_izq, unico_der;	

	if(raiz == NULL) {
		return 0;
	} else {
   		unico_izq = numHijoUnico(raiz->izq);
		unico_der = numHijoUnico(raiz->der);

		if(raiz->izq == NULL && raiz->der != NULL || raiz->izq != NULL && raiz->der == NULL) {
			return unico_izq + unico_der + 1;
		}
		return unico_izq + unico_der;
    }

}


Arbol buscarMax(Arbol raiz) {
	Arbol max,izq,der;		
	
	if(raiz == NULL) {
		return NULL;
	} else {
		max = raiz;
		izq = buscarMax(raiz->izq);
		der = buscarMax(raiz->der);
		
		if(izq != NULL && izq->info > max->info) max = izq;
		
		if(der != NULL && der->info > max->info) max = der;

		return max;
	}

}


Arbol buscarMin(Arbol raiz) {
	Arbol min,izq,der;		
	
	if(raiz == NULL) {
		return NULL;
	} else {
		min = raiz;
		izq = buscarMin(raiz->izq);
		der = buscarMin(raiz->der);
		
		if(izq != NULL && izq->info < min->info) min = izq;
		
		if(der != NULL && der->info < min->info) min = der;

		return min;
	}

}


int similares(Arbol r1,Arbol r2) {
	int izq,der;

	if(r1 == NULL && r2 == NULL) {
		return 1;
	} else {
		if ((r1 == NULL && r2 != NULL) || (r1 != NULL && r2 == NULL)) return 0;

		izq = similares(r1->izq,r2->izq);
		der = similares(r1->der,r2->der);

		if(izq == 1 && der == 1) return 1;
			else return 0;
	}

}


int equivalentes(Arbol r1,Arbol r2) {
	int izq,der;

	if(r1 == NULL && r2 == NULL) {
		return 1;
	} else {
		if ((r1 == NULL && r2 != NULL) || (r1 != NULL && r2 == NULL)) return 0;

		izq = equivalentes(r1->izq,r2->izq);
		der = equivalentes(r1->der,r2->der);

		if(izq == 1 && der == 1 && r1->info == r2->info) return 1;
			else return 0;
	}

}


/*Arbol especular(Arbol raiz) {
	Arbol izq,der,aux;

	if(raiz == NULL) {
		return NULL;
	} else {
		izq = especular(raiz->izq);
		der = especular(raiz->der);
		
		if(raiz->izq != NULL) aux->der=izq;
		
		if(raiz->der != NULL) aux->izq=der;

		return aux;
	}


}*/
