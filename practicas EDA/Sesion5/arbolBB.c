#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbolBB.h"


#ifdef EJERCICIO1
/******************************************************************
* Árboles Binarios de Búsqueda SIN CLAVES REPETIDAS
* Se incluye un poco de código para mostrar la diferencia entre   *
* insertar (paso por referencia) y buscar                         * 
*******************************************************************/

int insertar(tipoArbolBB *raiz,tipoClave clave) { 
	tipoNodo *nuevo;
    
	if ((nuevo = (tipoNodo *)malloc(sizeof(tipoNodo))) == NULL)
		return -1;
  	else {
		nuevo->clave = clave;
		nuevo->info = 1; 
    }

  	if (*raiz == NULL) {
		(*raiz) = nuevo;
		return 0;
	} else if (clave == (*raiz)->clave) {
		(*raiz)->info = (*raiz)->info + 1;
		return -1;
  	} else if (clave < (*raiz)->clave) {
        insertar(&((*raiz)->izq),clave);
	} else if (clave > (*raiz)->clave) {
		insertar(&((*raiz)->der),clave);
	}
}

int buscar(tipoClave clave,tipoArbolBB raiz, tipoNodo **nodo) {
	if (raiz == NULL) return 0;
	else if (clave == raiz->clave) {
		(*nodo) = raiz;
		return (*nodo)->info;
	} else if (clave < raiz->clave) {
    	buscar(clave,raiz->izq,nodo);
	} else if (clave > raiz->clave) {
    	buscar(clave,raiz->der,nodo);
	}
}

// Implementacion buscando el nodo mas derecha del subarbol izquierdo
int eliminar(tipoArbolBB *raiz, tipoClave clave) {
	tipoNodo *aux, *ant;
	
	if ((*raiz) == NULL) {
		return 0;
	} else if (clave < (*raiz)->clave) {
    	eliminar(&((*raiz)->izq),clave);
	} else if (clave > (*raiz)->clave) {
    	eliminar(&((*raiz)->der),clave);
	} else if (clave == (*raiz)->clave) {
		aux = (*raiz);
		if (aux->der == NULL) {
			(*raiz) = aux->izq;
			return (*raiz)->info;
		} else if (aux->izq == NULL) {
			(*raiz) = aux->der;
			return (*raiz)->info;
		} else {
			ant = aux;
			aux = aux->izq;
			
			while (aux->der != NULL) {
				ant = aux;
				aux = aux->der;
			}
			
			(*raiz)->clave = aux->clave;
			(*raiz)->info = aux->info;

			if (ant == (*raiz)) {
				ant->izq = aux->izq;
			} else {
				ant->der = aux->izq;
			}
		}	
	free(aux);
	return (*raiz)->info; 
	}
}

// Implementacion buscando el nodo mas izquierda del subarbol derecho
int eliminar2(tipoArbolBB *raiz, tipoClave clave) {
	tipoNodo *aux, *ant;

	if (raiz == NULL) return -1;
	else if (clave < (*raiz)->clave) {
    	eliminar(&((*raiz)->izq),clave);
	} else if (clave > (*raiz)->clave) {
    	eliminar(&((*raiz)->der),clave);
	} else if (clave == (*raiz)->clave) {
		aux = (*raiz);
		if (aux->der == NULL) {
			(*raiz) = aux->izq;
			return (*raiz)->info;
		} else if (aux->izq == NULL) {
			(*raiz) = aux->der;
			return (*raiz)->info;
		} else {
			ant = aux;
			aux = aux->der;
			
			while (aux->izq != NULL) {
				ant = aux;
				aux = aux->izq;
			}
			
			(*raiz)->clave = aux->clave;
			(*raiz)->info = aux->info;

			if (ant == (*raiz)) {
				ant->der = aux->der;
			} else {
				ant->izq = aux->der;
			}
		}
	free(aux);
	return (*raiz)->info;
	}
}

#endif

#ifdef EJERCICIO3
/******************************************************
* Árboles Binarios de Búsqueda CON CLAVES REPETIDAS   *
******************************************************/
int insertar(tipoArbolBB *raiz,tipoClave clave, tipoInfo info) { 
  	tipoNodo *nuevo, *aux, *ant;
	char i;
    
	if ((nuevo = (tipoNodo *)malloc(sizeof(tipoNodo))) == NULL)
		return -1;
  	else {
		nuevo->clave = clave;
		strcpy(nuevo->info, info);	
    }

  	if (*raiz == NULL) {
		(*raiz) = nuevo;
		return 0;
  	} else if (clave <= (*raiz)->clave) {
		if (clave == (*raiz)->clave) {
			if ((*raiz)->izq == NULL) {
				(*raiz)->izq = nuevo;
			} else {
				aux = (*raiz)->izq;
				(*raiz)->izq = nuevo;
				nuevo->izq = aux;				
			}	
		} else {
        	insertar(&((*raiz)->izq),clave,info);
		}
	} else if (clave > (*raiz)->clave) {
		insertar(&((*raiz)->der),clave,info);
	}
}


// Implementacion buscando el nodo mas derecha del subarbol izquierdo

//FALTA PONER BIEN EL CONTADOR DE VECES DEL RETURN
int eliminar(tipoArbolBB *raiz, tipoClave clave) {
 	tipoNodo *aux, *ant;
	int contador = 0;
	
	if ((*raiz) == NULL) {
		return 0;
	} else if (clave < (*raiz)->clave) {
    	eliminar(&((*raiz)->izq),clave);
	} else if (clave > (*raiz)->clave) {
    	eliminar(&((*raiz)->der),clave);
	} else if (clave == (*raiz)->clave) {
		aux = (*raiz);
		if (aux->der == NULL) {
			(*raiz) = aux->izq;
			contador++;
			eliminar(&((*raiz)),clave);
			return contador;
		} else if (aux->izq == NULL) {
			(*raiz) = aux->der;
			contador++;
			eliminar(&((*raiz)),clave);
			return contador;
		} else {
			ant = aux;
			aux = aux->izq;
			
			while (aux->der != NULL) {
				ant = aux;
				aux = aux->der;
			}
			
			(*raiz)->clave = aux->clave;
			strcpy((*raiz)->info, aux->info);	

			if (ant == (*raiz)) {
				ant->izq = aux->izq;
			} else {
				ant->der = aux->izq;
			}
		}	
	free(aux);
	contador++;
	eliminar(&((*raiz)),clave);
	return contador;
	}
}


// Implementacion buscando el nodo mas izquierda del subarbol derecho
int eliminar2(tipoArbolBB *raiz, tipoClave clave) {
	/*tipoNodo *aux, *ant;

	if (raiz == NULL) return -1;
	else if (clave < (*raiz)->clave) {
    	eliminar(&((*raiz)->izq),clave);
	} else if (clave > (*raiz)->clave) {
    	eliminar(&((*raiz)->der),clave);
	} else if (clave == (*raiz)->clave) {
		aux = (*raiz);
		if (aux->der == NULL) {
			(*raiz) = aux->izq;
			return (*raiz)->info;
		} else if (aux->izq == NULL) {
			(*raiz) = aux->der;
			return (*raiz)->info;
		} else {
			ant = aux;
			aux = aux->der;
			
			while (aux->izq != NULL) {
				ant = aux;
				aux = aux->izq;
			}
			
			(*raiz)->clave = aux->clave;
			(*raiz)->info = aux->info;

			if (ant == (*raiz)) {
				ant->der = aux->der;
			} else {
				ant->izq = aux->der;
			}
		}
	free(aux);
	return (*raiz)->info;
	}*/
}

#endif
/*****************************************************************************************
* Funciones GENERALES adaptadas a los dos ejercicios mediante DIRECTIVAS DE COMPILACIÓN  *
/*****************************************************************************************/
tipoNodo *creaNodo(tipoClave clave, tipoInfo info)
{ tipoNodo * nuevo;
  
  //   nuevo =(tipoNodo *)calloc(1, sizeof(tipoNodo));
  if ((nuevo =(tipoNodo *)malloc(sizeof(tipoNodo)))==NULL)
	return NULL;
  else 
  {	nuevo->clave = clave;
  	#ifdef EJERCICIO1
	nuevo->info=info;
  	#endif
  	#ifdef EJERCICIO3
	strcpy(nuevo->info,info);
  	#endif
  	nuevo->izq=NULL;
  	nuevo->der=NULL;
  return nuevo;
  }
}

void preOrden(tipoArbolBB a)
{ if (a) { 
  	#ifdef EJERCICIO1
	printf("%d %d \n", a->clave,a->info);
	#endif
  	#ifdef EJERCICIO3
	printf("%d %s \n", a->clave,a->info);
  	#endif
  	preOrden(a->izq);
  	preOrden(a->der);
  }
} 

void enOrden(tipoArbolBB a)
{ if (a) { 
	enOrden(a->izq);
   	#ifdef EJERCICIO1
	printf("%d %d \n", a->clave,a->info);
   	#endif
   	#ifdef EJERCICIO3
	printf("%d %s \n", a->clave,a->info);
   	#endif
    	enOrden(a->der);
  }
} 

void posOrden(tipoArbolBB a)
{ if (a) {
  	enOrden(a->izq);
  	enOrden(a->der);
   	#ifdef EJERCICIO1
	printf("%d %d \n", a->clave,a->info);
   	#endif
   	#ifdef EJERCICIO3
	printf("%d %s \n", a->clave,a->info);
   	#endif
  }
} 

