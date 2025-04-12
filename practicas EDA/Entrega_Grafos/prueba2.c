#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "grafos.h"


tipoGrafo *creaGrafoF1();


int main(void)
{ tipoGrafo *vGrafo;
  int ciclico,distancia,vIni,vFin;
  
	vGrafo = creaGrafoF1();
	iniciar(vGrafo);
	verGrafo(vGrafo);
  	printf("\nProfundidad: ");
  	profundidadMejorado(1,vGrafo); 	
 	printf("\nAmplitud : ");
 	amplitudMejorado(1,vGrafo);	
	ciclico = ordenTop2(vGrafo);
	if (ciclico==-1) 
		printf("\nGrafo ciclico ¡ No es posible la ordenación topológica !");
	else 
		verGrafo(vGrafo);

	// Prueba vertice 2 
	vIni=2;
  	printf("\nVersión mejorada Dijkstra: caminos mínimos desde %d",vIni);

  	dijkstra2(vIni,vGrafo);
	verGrafo(vGrafo);
	printf("\nCaminos Mínimos desde %d\n",vIni);
	todosCaminosMin(vIni,vGrafo);	



	// Prueba vertice 10 
	vIni=10;
  	printf("\nVersión mejorada Dijkstra: caminos mínimos desde %d",vIni);

  	dijkstra2(vIni,vGrafo);
	verGrafo(vGrafo);
	printf("\nCaminos Mínimos desde %d\n",vIni);
	todosCaminosMin(vIni,vGrafo);
  

	liberarListas(vGrafo);
	free(vGrafo);
}
/************************************************/
/* Creación del grafo ponderado de la Figura 1  */
/************************************************/
tipoGrafo *creaGrafoF1()
{ int i;
  pArco  p,aux;
  tipoGrafo *g;

  g=(tipoGrafo *)calloc(1,sizeof(tipoGrafo));

  g->orden=11;

  // Lista de adyacencia del vértice 1
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 2;
  	p->peso = 13;
  	g->directorio[1].lista=p;
  	aux = p;
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	  p->v = 6;
	  p->peso = 2;
	  aux->sig = p;
  p->sig=NULL;
  // Lista de adyacencia del vértice 2
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
  	p->v = 3;
	p->peso = 15;
  	g->directorio[2].lista=p;
  	p->sig=NULL;
  // Lista de adyacencia del vértice 3
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 6;
	p->peso = 4;
	g->directorio[3].lista=p;
	aux = p;
  p= (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 11;
	p->peso = 5;
	aux->sig=p;
  p->sig=NULL;
  // Lista de adyacencia del vértice 4
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 1;
	p->peso = 25;
	g->directorio[4].lista=p;
	aux = p;
  p= (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 5;
	p->peso = 2;
	aux->sig = p;
	aux = aux->sig;
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 8;
	p->peso = 10;
	aux->sig = p;
	aux = aux->sig;
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 9;
	p->peso = 4;
	aux->sig = p;
  p->sig=NULL;
// Lista de adyacencia del vértice 5
  g->directorio[5].lista=NULL;
// Lista de adyacencia del vértice 6
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 2;
	p->peso = 3;
	g->directorio[6].lista=p;
	aux = p;
  p= (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 5;
	p->peso = 2;
	aux->sig = p;
	aux = aux->sig;
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 7;
	p->peso = 30;
	aux->sig = p;
	aux = aux->sig;
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 10;
	p->peso = 4;
	aux->sig = p;
  p->sig=NULL;
// Lista de adyacencia del vértice 7
  g->directorio[7].lista=NULL;
// Lista de adyacencia del vértice 8
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
  	p->v = 9;
	p->peso = 6;
  	g->directorio[8].lista=p;
  	p->sig=NULL;
// Lista de adyacencia del vértice 9
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 6;
	p->peso = 13;
	g->directorio[9].lista=p;
	aux = p;
  p= (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 10;
	p->peso = 2;
	aux->sig=p;
  p->sig=NULL;
// Lista de adyacencia del vértice 10
  p = (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 7;
	p->peso = 1;
	g->directorio[10].lista=p;
	aux = p;
  p= (arco *)calloc(1,sizeof(arco));	 if (!p) liberarListas(g);		
	p->v = 11;
	p->peso = 2;
	aux->sig=p;
  p->sig=NULL;
// Lista de adyacencia del vértice 11
  g->directorio[11].lista=NULL;

  return g;
  }

