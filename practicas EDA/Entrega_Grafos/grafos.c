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

/***************************************************************************************************/
/* Recorrido en PROFUNDIDAD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/***************************************************************************************************/
void profundidad(int v_inicio,tipoGrafo * grafo) { 
  int w;
  pArco p;

  printf("%d ",v_inicio);
  grafo->directorio[v_inicio].alcanzado=1;
  p = grafo->directorio[v_inicio].lista;
  while (p!=NULL)
  { w=p->v;
    if (!grafo->directorio[w].alcanzado)
        profundidad(w,grafo);
    p = p->sig;
  }
}

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
/* Recorrido en AMPLITUD de un grafo. ¡CUIDADO! Depende del vertice inicial y del tipo de grafo */
/************************************************************************************************/
void amplitud(int v_inicio,tipoGrafo *grafo) { 
  int w;
  pArco p;
  Cola c;

  colaCreaVacia(&c);
  colaInserta(&c,v_inicio);
  while (!colaVacia(&c))  {
	w = colaSuprime(&c);
    if (!grafo->directorio[w].alcanzado) {
		printf("%d ",w);
	    grafo->directorio[w].alcanzado=1;
       	p = grafo->directorio[w].lista;
	 	while (p != NULL){
			w = p->v;
			colaInserta(&c,w);
			p = p->sig;
		}
	}
  }
}

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
/* Función auxiliar para ver el contenido de la estructura que representa un grafo en memoria */
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
	
	for(orden = 1; orden <= g->orden; orden++) {
		p = g->directorio[orden].lista;
		while(p != NULL) {
				w = p->v;
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
		v = buscarVerticeGradoCeroNoOrdenTop(grafo);
		if(v == -1) {
			return -1;
		} else {
			grafo->directorio[v].ordenTop = orden;
			p = grafo->directorio[v].lista;
			while(p != NULL) {
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
		if(grafo->directorio[orden].gradoEntrada == 0) return orden;
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
	for(v = 1; v <= grafo->orden; v++) {
		if(grafo->directorio[v].gradoEntrada == 0) colaInserta(&c,v);
	}
	orden = 1;
	
	while(!colaVacia(&c)) {
		v = colaSuprime(&c);			
		grafo->directorio[v].ordenTop = orden;
		orden = orden + 1;
		p = grafo->directorio[v].lista;
		while(p != NULL) {
			w = p->v;
			grafo->directorio[v].gradoEntrada = grafo->directorio[w].gradoEntrada - 1;
			if(grafo->directorio[w].gradoEntrada == 0) colaInserta(&c,w);
			p = p->sig;
		}
	}

	if(orden != grafo->orden) { 
		return -1;
	}
	
	return 0;
}


/* Ejercicio 3: Caminos mínimos en grafos dirigidos */

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
			if(!g->directorio[v].alcanzado && g->directorio[v].distancia == distanciaActual) {
				g->directorio[v].alcanzado = 1;
				p = g->directorio[v].lista;
				
				while(p != NULL) {
					w = p->v;
					if(g->directorio[w].distancia == INF) {
						g->directorio[w].distancia = g->directorio[v].distancia + 1;
						g->directorio[w].anterior = v; 
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
	colaInserta(&c,vInicio);

	while(!colaVacia(&c)) {
		v = colaSuprime(&c);			
		p = g->directorio[v].lista;
		while(p != NULL) {
			w = p->v;
			if(g->directorio[w].distancia == INF) {
				g->directorio[w].distancia = g->directorio[v].distancia + 1;
				g->directorio[w].anterior = v; 
				colaInserta(&c,w);
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
		v = buscarVerticeDistanciaMinimaNoAlcanzado(g);
		g->directorio[v].alcanzado = 1;
		p = g->directorio[v].lista;

		while(p != NULL) {
			w = p->v;
			if(g->directorio[w].alcanzado == 0) {
				if(g->directorio[v].distancia + p->peso < g->directorio[w].distancia) {
					g->directorio[w].distancia = g->directorio[v].distancia + p->peso;
					g->directorio[w].anterior = v; 
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
		if(g->directorio[orden].alcanzado == 0  && aux == 0) aux = orden;

		if(g->directorio[orden].alcanzado == 0  && g->directorio[orden].distancia < g->directorio[aux].distancia) aux = orden;
	}
	return aux;
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
	x.clave = 0;
	x.informacion = vInicio;
	insertar(x,&m);
	
	while(!vacioMonticulo(m)) {
		eliminarMinimo(&m,&x); 
		if(!g->directorio[x.informacion].alcanzado) {
			v = x.informacion;
			g->directorio[v].alcanzado = 1;
			p = g->directorio[v].lista;
	
			while(p != NULL) {
				w = p->v;
				if(!g->directorio[w].alcanzado) {
					coste = g->directorio[v].distancia + p->peso;
					if(coste < g->directorio[w].distancia) {
						g->directorio[w].distancia = coste;
						g->directorio[w].anterior = v;
						x.clave = g->directorio[w].distancia;
						x.informacion = w;
					 	insertar(x,&m);
					}
				}
				p = p->sig;
			}
		}
	}
}


/* Interpretación de los algoritmos ¡Secuencia de vértices en caminos mínimos y distancias !!! */
int costeyTrayectoria(int vIni, int vFin, tipoGrafo *g) {
	int v;
	Pila p;

	if(g->directorio[vFin].distancia == INF) { 
		return INF;
	}	
	
	v = vFin;
	pilaCreaVacia(&p);
	pilaInserta(&p,vFin);
		
	while(g->directorio[v].anterior != vIni) {
		v = g->directorio[v].anterior;		
		pilaInserta(&p,v);	
	}
	pilaInserta(&p,vIni);

	while(!pilaVacia(&p)) {
		v = pilaSuprime(&p);
		printf(" %d ",v);
	}	
	
	return g->directorio[vFin].distancia;
}


void todosCaminosMin(int vIni, tipoGrafo *g) {
	int orden;
	int coste;
	
	for(orden = 1; orden <= g->orden; orden++) {
		if(orden != vIni) {
			coste = costeyTrayectoria(vIni,orden, g);
			printf("\t\tCoste camino a vertice %d: %d\n",orden,coste);
		}
	}
}


void liberarListas(tipoGrafo *g) {
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
