/*
 * grafos.c
 *
 *  Created on: 21/04/2014
 *      Author: MJ Polo
 */
#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#include "grafos.h"
#include "monticulo.h"
#include "pila.h"
#include "conjuntos.h"

/***************************************************************************************************/
/* Recorrido en PROFUNDIDAD de un grafo. Â¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/***************************************************************************************************/
void profundidad(int v_inicio,tipoGrafo * grafo) { 
  int w;
  pArco p;

  printf("%d ",v_inicio);
  grafo->directorio[v_inicio].alcanzado=1; // Se marca como alcanzado el vertice inicial
  p = grafo->directorio[v_inicio].lista;
  while (p!=NULL) // Se recorre la lista de adyacencia del vertice inicial
  { w=p->v;
    if (!grafo->directorio[w].alcanzado) // Si el vertice de la lista de adyacencia no ha sido alcanzado
        profundidad(w,grafo); // Se hace el recorrido en profundidad del grafo
    p = p->sig;
  }
}


// Se hace un ciclo por si ha quedado algun vertice que no ha realizado el profundidad
void profundidadMejorado(int v_inicio,tipoGrafo * grafo) { 
  int orden;	

  iniciar(grafo);

  profundidad(v_inicio,grafo);
  for(orden = 1; orden < grafo->orden; orden++) {
		if(!grafo->directorio[orden].alcanzado) {
			profundidad(orden,grafo);		
		}
  }
}
/************************************************************************************************/
/* Recorrido en AMPLITUD de un grafo. Â¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/************************************************************************************************/
void amplitud(int v_inicio,tipoGrafo *grafo) { 
  int w;
  pArco p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c,v_inicio); // Se insera en la cola el vertice inicial
  while (!colaVacia(&c))  {
	w = colaSuprime(&c); // Se suprime de la cola el primer elemento
    if (!grafo->directorio[w].alcanzado) { // Si el elemento que se ha suprimido de la cola no esta alcanzado
		printf("%d ",w);
	    grafo->directorio[w].alcanzado=1; // Se marca como alcanzado
       	p = grafo->directorio[w].lista;
	 	while (p != NULL){ // Se recorre la lista de adyacencia del grafo suprimido de la cola
			w = p->v;
			colaInserta(&c,w); // Se insertan en la cola los elementos de la lista de adyacencia
			p = p->sig;
		}
	}
  }
}


// Se hace un ciclo por si ha quedado algun vertice que no ha realizado el amplitud
void amplitudMejorado(int v_inicio,tipoGrafo *grafo) { 
  int orden;
	
	iniciar(grafo);

	amplitud(v_inicio,grafo);
	for(orden = 1; orden <= grafo->orden; orden++) {
		if(!grafo->directorio[orden].alcanzado) {
			amplitud(orden,grafo);		
		}
	}	  
}
/**********************************************************************************************/
/* FunciÃ³n auxiliar para ver el contenido de la estructura que representa un grafo en memoria */
/**********************************************************************************************/
void verGrafo(tipoGrafo *g)
{  int i;
   pArco p;

   printf("\nGrafo  (Orden %d)\n\n",g->orden);
   printf("       alc gEnt oTop dist peso ant \n");
   printf("     +----+----+----+----+----+----+\n");

   for(i=1;i<=g->orden;i++)
   {  printf("  %2d | %2d | %2d | %2d |", i, g->directorio[i].alcanzado,
                       g->directorio[i].gradoEntrada, g->directorio[i].ordenTop);
       if (g->directorio[i].distancia == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].distancia);
       if (g->directorio[i].peso == INF) printf("  * |");
       else   printf(" %2d |", g->directorio[i].peso);
       printf(" %2d |",g->directorio[i].anterior);
       p = g->directorio[i].lista;
       while (p != NULL)
       {   //printf(" ->%2d", p->v);	// Grafos no ponderados
           printf(" ->%2d, %2d", p->v, p->peso); // Grafos ponderados
           p = p->sig;
       }
       printf("\n");
   }
   printf("     +----+----+----+----+----+----+\n\n");
}


/* Ejercicio 1 */

void iniciar(tipoGrafo *g) {
	int orden;
	int w;	
	pArco p;

	for(orden = 1; orden <= g->orden; orden++) {
		g->directorio[orden].alcanzado = 0;
		g->directorio[orden].ordenTop = 0;
		g->directorio[orden].anterior = 0;
		g->directorio[orden].distancia = INF;
		g->directorio[orden].peso = INF;
		g->directorio[orden].gradoEntrada = 0;  
	}
	
	for(orden = 1; orden <= g->orden; orden++) { // Se recorre la lista de adayacencia de cada uno de los vertices
		p = g->directorio[orden].lista;
		while(p != NULL) {
				w = p->v; // Se suma 1 al grado de netrada del elemento de la lista de adyacencia
				g->directorio[w].gradoEntrada = g->directorio[w].gradoEntrada + 1;
				p = p->sig;			
			}
	}
}


/* Ejercicio 2 */

int ordenTop1(tipoGrafo *grafo) {
	int orden;
	pArco p;
	int v,w;
	
	iniciar(grafo);
	for(orden = 1; orden <= grafo->orden; orden++) {
		v = buscarVerticeGradoCeroNoOrdenTop(grafo); // Busca el vertice del grafo que tiene grado de entrada = 0
		if(v == -1) {
			return -1;
		} else {
			grafo->directorio[v].ordenTop = orden; // Le asigna el numero de orden topologico que le corrresponde
			p = grafo->directorio[v].lista; 
			while(p != NULL) {  // Se recorre la lista de adyacencia del vertice disminuyendo en 1 el grado de entrada
				w = p->v;
				grafo->directorio[w].gradoEntrada = grafo->directorio[w].gradoEntrada - 1;
				p = p->sig;			
			}
		}
	}
}

int buscarVerticeGradoCeroNoOrdenTop(tipoGrafo *grafo) {
	int orden;	
	
	for(orden = 1; orden <= grafo->orden; orden++) {
		if(grafo->directorio[orden].gradoEntrada == 0 && grafo->directorio[orden].ordenTop == 0) return orden;
	}
	return -1;
}

int ordenTop2(tipoGrafo *grafo) {
	int orden;	
	pArco p;
	Cola c;
	int v,w;

	iniciar(grafo);
	colaCreaVacia(&c);
	for(v = 1; v <= grafo->orden; v++) { // Se insertan en la cola todos los vertices con grado de entrada 0
		if(grafo->directorio[v].gradoEntrada == 0) colaInserta(&c,v);
	}
	orden = 1;
	
	while(!colaVacia(&c)) {
		v = colaSuprime(&c); // Se suprime el primer elemento de la cola			
		grafo->directorio[v].ordenTop = orden; // Le asigna el numero de orden que le corrresponde 
		orden = orden + 1;
		p = grafo->directorio[v].lista;
		while(p != NULL) { // Se recorre la lista de adyacencia del vertice disminuyendo en 1 el grado de entrada
			w = p->v;
			grafo->directorio[v].gradoEntrada = grafo->directorio[w].gradoEntrada - 1;
			if(grafo->directorio[w].gradoEntrada == 0) colaInserta(&c,w); //Si el grado de entrada de algún vértice se convierte en cero, se inserta en la cola
			p = p->sig;
		}
	}

	if(orden != grafo->orden) { // Si la variable orden al acabar la funcion con coincide con el orden del grafo se devuelve error
		return -1;
	}
	
	return 0;
}


/* Ejercicio 3: Caminos mÃ­nimos en grafos dirigidos */

/* a) NO Ponderados */
void caminos1(int vInicio, tipoGrafo *g) {
	int distanciaActual;
	int v,w;
	pArco p;
	
	iniciar(g);
	g->directorio[vInicio].distancia = 0;
	g->directorio[vInicio].anterior = 0;

	for(distanciaActual = 0; distanciaActual <= g->orden-1; distanciaActual++) { 
		for(v = 1; v <= g->orden; v++) {
			if(!g->directorio[v].alcanzado && g->directorio[v].distancia == distanciaActual) { // Se busca el vertice que tenga como valor distancia distanciaActual
				g->directorio[v].alcanzado = 1; // Se le pone el campo alcanzado a 1
				p = g->directorio[v].lista;
				
				while(p != NULL) { // Se recorre su lista de adyacencia
					w = p->v;
					if(g->directorio[w].distancia == INF) { // Si la distancia del vertice de la lista de adyacencia es INFINITO , es decir, no se ha llegado aun
						g->directorio[w].distancia = g->directorio[v].distancia + 1; // Se le asigna la distacia del vertice mas 1
						g->directorio[w].anterior = v; // El campo anterior del vertice de la lista de adyacencia sera el vertice
					}
					p = p->sig;
				}
			}
		}
	}
}


void caminos2(int vInicio, tipoGrafo *g) {
	int v,w;
	pArco p;
	Cola c;
	
	iniciar(g);
	g->directorio[vInicio].distancia = 0;
	g->directorio[vInicio].anterior = 0;

	colaCreaVacia(&c);
	colaInserta(&c,vInicio); // Se almacena el vertice de partida en la cola

	while(!colaVacia(&c)) {
		v = colaSuprime(&c); // Se suprime el primer elemento de la cola 			
		p = g->directorio[v].lista;
		while(p != NULL) { // Se recorre su lista de adyacencia
			w = p->v;
			if(g->directorio[w].distancia == INF) { // Si la distancia del vertice de la lista de adyacencia es INFINITO , es decir, no se ha llegado aun
				g->directorio[w].distancia = g->directorio[v].distancia + 1; // Se le asigna la distacia del vertice mas 1
				g->directorio[w].anterior = v; 
				colaInserta(&c,w); // Se almacena en la cola el vertice de la lista de adyacencia
			}
			p = p->sig;
		}
	}
}


/* b) PONDERADOS */
void dijkstra1(int vInicio, tipoGrafo *g) {
	int v,w;
	pArco p;
	int i;

	iniciar(g);
	g->directorio[vInicio].distancia = 0;
	g->directorio[vInicio].anterior = 0;

	for(i = 1; i <= g->orden; i++) {
		v = buscarVerticeDistanciaMinimaNoAlcanzado(g); // v es el vertice con menor distacia no alcanzado
		g->directorio[v].alcanzado = 1; // Se marca como alcanzado
		p = g->directorio[v].lista;

		while(p != NULL) { // Se recorre su lista de adyacencia
			w = p->v;
			if(g->directorio[w].alcanzado == 0) { // Si el vertice la lista de adyacencia no ha sido alcanzado todavia
				if(g->directorio[v].distancia + p->peso < g->directorio[w].distancia) { // Si al sumar la distancia del vertice al peso de la arista resulta un numero menor de la distancia que ya tenia el vertice de la lista de adyacencia se cambia la distancia
					g->directorio[w].distancia = g->directorio[v].distancia + p->peso; // Se le asigna la nueva distancia al vertice de la lista de adyacencia (distancia del vertice + peso de la arista) 
					g->directorio[w].anterior = v; // Se cambia el campo anterior del vertice de la lista de adyacencia a la del vertice
				}
			}
			p = p->sig;
		}
	}
}

int buscarVerticeDistanciaMinimaNoAlcanzado(tipoGrafo *g) { 
	int orden;
	int aux = 0;	
	
	for(orden = 1; orden <= g->orden; orden++) {
		if(g->directorio[orden].alcanzado == 0  && aux == 0) aux = orden; // Para la primera ejecucion del bucle

		if(g->directorio[orden].alcanzado == 0  && g->directorio[orden].distancia < g->directorio[aux].distancia) aux = orden; // Si se encuentra otro vertice con menos distancia que aux sera el nuevo aux
	}
	return aux; // Se retorna el vertice no alcanzado con menor distacia del grafo
}


void dijkstra2(int vInicio, tipoGrafo *g) {
	int v,w;
	pArco p;
	int i;
	int coste;
	Monticulo m;
	tipoElementoMon x;

	iniciar(g);
	g->directorio[vInicio].distancia = 0;
	g->directorio[vInicio].anterior = 0;
	iniciaMonticulo(&m);
	x.clave = 0; // Distancia 0 al ser el vertice inicial
	x.informacion = vInicio;
	insertar(x,&m); // Se inserta en el monticulo el elemento x que contine el vertice inicial
	
	while(!vacioMonticulo(m)) {
		eliminarMinimo(&m,&x); // Funcion que elimina el elemento minimo del monticulo (monticulo.c) y que devuelve el elemento eliminado
		if(!g->directorio[x.informacion].alcanzado) { // Si el vertice que se ha eliminado del monticulo no esta alcanzado
			v = x.informacion;
			g->directorio[v].alcanzado = 1; // Se marca como alcanzado 
			p = g->directorio[v].lista;
	
			while(p != NULL) { // Se recorre su lista de adyacencia
				w = p->v;
				if(!g->directorio[w].alcanzado) { // Si el vertice la lista de adyacencia no ha sido alcanzado todavia
					coste = g->directorio[v].distancia + p->peso; // coste es la suma de la distancia del vertice mas el peso de la arista
					if(coste < g->directorio[w].distancia) { // Si el coste resulta menor que la distancia que tenia el vertice de la lista de adyacencia
						g->directorio[w].distancia = coste; // Se le asigna el nuevo coste al vertice de la lista de adyacencia
						g->directorio[w].anterior = v; // Se cambia el campo anterior del vertice de la lista de adyacencia a la del vertice
						x.clave = g->directorio[w].distancia; // Se actualiza los campos con la nueva distancia para insertarlo de nuevo en el monticulo
						x.informacion = w;
					 	insertar(x,&m); // Se inserta la informacion actualizada en el monticulo
					}
				}
				p = p->sig;
			}
		}
	}
}


/* InterpretaciÃ³n de los algoritmos Â¡Secuencia de vÃ©rtices en caminos mÃ­nimos y distancias !!! */
int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g) { // Ejemplo en la diapositiva 40
	int v;
	Pila p;

	if(g->directorio[vFin].distancia == INF) { // Si el vertice final tiene distancia infinita ( es inaccesible) se devuelve infinito
		return INF;
	}	
	
	v = vFin;
	pilaCreaVacia(&p);
	pilaInserta(&p,vFin); // Se inserta el vertice final en la pila
		
	while(g->directorio[v].anterior != vIni) { // Mientras que el vertice no tenga en su campo anterior el vertice inicial
		v = g->directorio[v].anterior;	// Se asigna v al campo anterior del vertice	
		pilaInserta(&p,v);	// Se inserta el vertice que estaba en el campo anterior
	}
	pilaInserta(&p,vIni); // Cuando acabe el bucle se inserta el vertice inicial (El unico que faltaba en la trayectoria)

	while(!pilaVacia(&p)) { // Mientras que no se vacie la pila
		v = pilaSuprime(&p); // Se suprime el elemento de la pila (Va en orden contrario a como se inserta, es decir, ira desde el vertice inicial al final)
		printf(" %d ",v);
	}	
	
	return g->directorio[vFin].distancia; // Se devuelve la distancia de la trayectoria del camino (Campo distancia del vertice final)
}


void todosCaminosMin(int vIni, tipoGrafo *g) {  // Funcion que ejecutara un bucle que recorra todo el grafo (menos vIni) y calcule el coste del camino
	int orden;
	int coste;
	
	for(orden = 1; orden <= g->orden; orden++) {
		if(orden != vIni) {
			coste = costeyTrayectoria(vIni,orden, g);
			printf("\t\tCoste camino a vertice %d: %d\n",orden,coste); // Se imprime el coste del camino del vertice orden y su coste
		}
	}
}


void liberarListas(tipoGrafo *g) { // Funcion que recorre el grafo y va liberando su lista de adyacencia (No se si esta bien)
	int i;
	pArco aux,p;

	for(i = 1; i <= g->orden; i++) {
		p = g->directorio[i].lista;

		while(p != NULL) {
			aux = p;
			p = aux->sig;
			free(aux);
		}
	}
}



/* Ejercicio 4: Árbol de Expansión en grafos NO dirigidos */
/* a) Prim  ¡ Algoritmo e interpretación del resultado!!! */
tipoGrafo * prim1(int vInicio, tipoGrafo *grafo) {
	int v,w;
	pArco p;
	int i;

	iniciar(grafo);
	grafo->directorio[vInicio].peso = 0;
	grafo->directorio[vInicio].anterior = 0;

	for(i = 1; i <= grafo->orden; i++) {
		v = buscarVerticeCostoMinimoNoAlcanzado(grafo); // v es el vertice con menor peso no alcanzado
		grafo->directorio[v].alcanzado = 1; // Se marca como alcanzado
		p = grafo->directorio[v].lista;

		while(p != NULL) { // Se recorre su lista de adyacencia
			w = p->v;
			if(grafo->directorio[w].alcanzado == 0) {
				if(p->peso < grafo->directorio[w].peso) { // Si el peso de la arista es menor que el peso de la arista que contiene el elemento de la lista de adyacencia
					grafo->directorio[w].peso = p->peso; // El nuevo peso del elemento de la lista de adyacencia es el peso de la arista
					grafo->directorio[w].anterior = v; // Se cambia el campo anterior del vertice de la lista de adyacencia a la del vertice
				}
			}
			p = p->sig;
		}
	}
	return grafo;
}

int buscarVerticeCostoMinimoNoAlcanzado(tipoGrafo *grafo) {
	int orden;
	int aux = 0;	
	
	for(orden = 1; orden <= grafo->orden; orden++) {
		if(grafo->directorio[orden].alcanzado == 0  && aux == 0) aux = orden; // Para la primera ejecucion del bucle

		if(grafo->directorio[orden].alcanzado == 0  && grafo->directorio[orden].peso < grafo->directorio[aux].peso) aux = orden; // Si se encuentra otro vertice con menos peso que aux sera el nuevo aux
	}
	return aux; // Se retorna el vertice no alcanzado con menor peso del grafo
}


tipoGrafo * prim2(int vInicio, tipoGrafo *grafo) {
	int v,w;
	pArco p;
	int i;
	int coste;
	Monticulo m;
	tipoElementoMon x;

	iniciar(grafo);
	grafo->directorio[vInicio].peso = 0;
	grafo->directorio[vInicio].anterior = 0;
	iniciaMonticulo(&m);
	x.clave = 0;
	x.informacion = vInicio;
	insertar(x,&m); // Se inserta en el monticulo el elemento x que contine el vertice inicial
	
	while(!vacioMonticulo(m)) {
		eliminarMinimo(&m,&x); // Funcion que elimina el elemento minimo del monticulo (monticulo.c) y que devuelve el elemento eliminado
		if(!grafo->directorio[x.informacion].alcanzado) { // Si el vertice que se ha eliminado del monticulo no esta alcanzado
			v = x.informacion;
			grafo->directorio[v].alcanzado = 1; // Se marca como alcanzado
			p = grafo->directorio[v].lista;
	
			while(p != NULL) { // Se recorre su lista de adyacencia
				w = p->v;
				if(!grafo->directorio[w].alcanzado) { // Si el vertice la lista de adyacencia no ha sido alcanzado todavia
					coste = p->peso; // El coste sera el peso de la arista
					if(coste < grafo->directorio[w].peso) { // Si el coste es menor que el peso que tiene el elemento de la lista de adyacencia
						grafo->directorio[w].peso = coste; // Se cambia a el coste del elemento de la lista de adyacencia
						grafo->directorio[w].anterior = v; // Se cambia el campo anterior del vertice de la lista de adyacencia a la del vertice
						x.clave = grafo->directorio[w].peso; // Se actualiza los campos con el nuevo peso para insertarlo de nuevo en el monticulo
						x.informacion = w;
					 	insertar(x,&m); // Se inserta la informacion actualizada en el monticulo
					}
				}
				p = p->sig;
			}
		}
	}
	return grafo;
}


/* c) Kruskal*/
tipoGrafo * kruskal(tipoGrafo *grafo) {
	Monticulo m;
	int numAristasAceptadas;
	particion C;
	tipoConjunto conjuntoU, conjuntoV;
	tipoElementoMon x;
	tipoGrafo *arbolExp;
	int orden, i;
	pArco p, aux;

	// Se crea el arbol de expansion
	arbolExp = (tipoGrafo *)calloc(1,sizeof(tipoGrafo));
	arbolExp->orden = grafo->orden; // Se iguala el orden del arbol de expansion al del grafo
	
	for(i = 1; i <= arbolExp->orden; i++) {
		arbolExp->directorio[i].lista = NULL;	// Se inician todas las listas de adyacencias a NULL
	}

	crea(C); // Se crea la particion C
	
	//Se construye el monticulo de aristas
	for(i = 1; i <= grafo->orden; i++) { // Para cada vertice se reecorre su lista de adyacencia y se añaden sus elementos
		p = grafo->directorio[i].lista;
		while(p != NULL) {
			x.clave = p->peso; // El peso de la arista sera el campo clave
			x.informacion = i; // EL primer vertice que une la arista sera el campo i
			x.informacion2 = p->v; // EL primer vertice que une la arista sera el campo p->v
			insertar(x,&m); // Se inserta en el monticulo
			p = p->sig;
		}
	}

	numAristasAceptadas = 0;
	
	while(numAristasAceptadas < grafo->orden -1) {
		eliminarMinimo(&m,&x); // Se elimina el elemento minimo del monticulo
		conjuntoU = buscar(x.informacion, C); // Se buscan los representantes de cada conjunto
		conjuntoV = buscar(x.informacion2, C); 

		if(conjuntoU != conjuntoV) { // Si no son iguales, es decir, no pertenecen al mismo conjunto
			unir(conjuntoU,conjuntoV,C); // Se unen
			numAristasAceptadas = numAristasAceptadas + 1; // Se aumenta el numero de aristas aceptadas
			
			// Se acepta la arista

			// Codigo para introducir el primer vertice en la lista del segundo
			aux = (arco *) calloc(1,sizeof(arco)); 
			aux->v = x.informacion; // Se rellenan los campos del primer vertice
			aux->peso = x.clave;
			aux->sig = NULL;

			if(arbolExp->directorio[x.informacion2].lista == NULL) { // Si la lista del segundo vertice esta vacia
				arbolExp->directorio[x.informacion2].lista = aux; // Se introduce aux (primer vertice) en la lista del segundo vertice
			} else { // Si la lista del segundo vertice no estaba vacia
				p = arbolExp->directorio[x.informacion2].lista;

				while(p != NULL) { // Se recorre la lista hasta el final
					if(p->sig == NULL) { // Si se ha llegado al final
						p->sig = aux; //Se introduce aux (primer vertice) al final de la lista del segundo vertice
						break;
					}
					p = p->sig;
				}
			}

			// Codigo para introducir el segundo vertice en la lista del primero
			aux = (arco *) calloc(1,sizeof(arco));
			aux->v = x.informacion2; // Se rellenan los campos del segundo vertice
			aux->peso = x.clave;
			aux->sig = NULL;

			if(arbolExp->directorio[x.informacion].lista == NULL) { // Si la lista del primer vertice esta vacia
				arbolExp->directorio[x.informacion].lista = aux; // Se introduce aux (segundo vertice) en la lista del primer vertice
			} else { // Si la lista del primer vertice no estaba vacia
				p = arbolExp->directorio[x.informacion].lista;
				while(p != NULL) { // Se recorre la lista hasta el final
					if(p->sig == NULL) { // Si se ha llegado al final
						p->sig = aux; //Se introduce aux (segundo vertice) al final de la lista del primer vertice
						break;
					}
					p = p->sig;
				}
			}
		}	
	}
	
	iniciar(arbolExp); // Se inicial el arbol de expansion
	return arbolExp; // Se devuelve el arbol de expansion
}


/* Ejercicio 3 FInal De Tema: Grafo conexo */

int conexo(tipoGrafo *grafo) {
	Monticulo m;
	int numAristasAceptadas;
	particion C;
	tipoConjunto conjuntoU, conjuntoV;
	tipoElementoMon x;
	int orden, i, j;
	pArco p;


	crea(C); // Se crea la particion C
	
	//Se construye el monticulo de aristas
	for(i = 1; i <= grafo->orden; i++) {
		p = grafo->directorio[i].lista;
		while(p != NULL) {
			x.clave = p->peso; // El peso de la arista sera el campo clave
			x.informacion = i; // EL primer vertice que une la arista sera el campo i
			x.informacion2 = p->v; // EL primer vertice que une la arista sera el campo p->v
			insertar(x,&m); // Se inserta en el monticulo
			p = p->sig;
		}
	}

	numAristasAceptadas = 0;
	while(numAristasAceptadas < grafo->orden -1) {
		eliminarMinimo(&m,&x); // Se elimina el elemento minimo del monticulo
		conjuntoU = buscar(x.informacion, C); // Se buscan los representantes de cada conjunto
		conjuntoV = buscar(x.informacion2, C); 

		if(conjuntoU != conjuntoV) { // Si no son iguales, es decir, no pertenecen al mismo conjunto
			unir(conjuntoU,conjuntoV,C); // Se unen
			numAristasAceptadas = numAristasAceptadas + 1;
		}	
	}
	
	for(i = 1; i <= grafo->orden; i++) { // Se recorre todo el grafo
		for(j = 1; j <= grafo->orden; j++) { // Se recorre todo el grafo
			conjuntoU = buscar(i, C); // Se busca los representantes de cada conjunto
			conjuntoV = buscar(j, C);  
	
			if(conjuntoU != conjuntoV) { // Si alguna de las comparaciones es falsa significa que no pertenecen al mismo conjunto por lo que el grafo no es conexo
				return 0; // Se devuelve falso (El grafo no es conexo)	
			}
		}
	}
	return 1; // Se devuelve verdadero (El grafo es conexo)
}
