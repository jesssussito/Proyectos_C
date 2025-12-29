#define N 10
#define INFINITO 9999
#include "../Monticulos/prototiposM.h"
#include "../Asociaciones/ArbolAsoc.h"
typedef struct nodo{
    int idV1,idV2;
    int coste;
    struct nodo *sig;
}tipoArco;
typedef struct vertice{
    int id;
    int alcanzado;
    int gradoEnt;
    int ordenTopo;
    int ant;
    int dist;
    int peso;
    //datos
    tipoNodo *listaAdyacencia;
}tipoVertice;
typedef struct{
    tipoVertice directorio[N];
    int orden;
}tipoGrafo;
void iniciarGrafo(tipoGrafo *G){
    int i;
    tipoArco *aux;
    for ( i = 0; i < G->orden; i++)//Recorro Vertices
    {
        G->directorio[i].ordenTopo=-1;
        G->directorio[i].gradoEnt=0;
        G->directorio[i].dist=INFINITO;
    }
    for ( i = 0; i < G->orden; i++)
    {
        aux=G->directorio[i].listaAdyacencia;
        while (aux!=NULL)//Recorro Listas
        {
            G->directorio[aux->idV].gradoEnt++;
            //Veo desde idV a que otros vertices llego
            aux = aux->sig;
        }
        
    }
    
}
void amplitudG(tipoGrafo *G, int vIni);
void amplitudGExt(tipoGrafo *G, int vIni);
void profundidadG(tipoGrafo *G, int vAct);
void profundidadGExt(tipoGrafo *G, int vAct);
int obtenerVsinOrdenEnt(tipoGrafo *G);
void ordenTopolog(tipoGrafo *G);
void ordenTopologCola(tipoGrafo *G);
void caminoMin(tipoGrafo *G,int vIni);
void caminoMinCola(tipoGrafo *G,int vIni);
int obtenerVDistMinNoAlcanzado(tipoGrafo *G);
void Dijkstra(tipoGrafo *G,int vIni);
void DijkstraMont(tipoGrafo *G,int vIni);
void PRIM(tipoGrafo *G,int vIni);
void KRUSKAL(tipoGrafo *G);
void aceptarArista(tipoGrafo *G,tipoElemento e);
void crearMonticuloAristas(tipoGrafo *G,Monticulo *M);
tipoGrafo generarAExp(tipoGrafo*G);
