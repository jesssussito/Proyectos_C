#include "definiciones.h"
typedef struct tipoE{
    int idV1,idV2,coste;
}tipoElementoD;


int obtenerVDistMinNoAlcanzado(tipoGrafo *G){
    int i;
    int vMin=_1;
    for ( i = 0; i < G->orden; i++)
    {
        if (G->directorio[i].alcanzado== 0 && (vMin == -1 || G->directorio[i].dist < G->directorio[vMin].dist))
        {
            vMin = i;
        }
    }
    return vMin;
}
void Dijkstra(tipoGrafo *G,int vIni){
    int vAct,i,distNueva;
    tipoArco *aux;
    iniciarGrafo(G);
    G->directorio[vIni].ant=-1;
    G->directorio[vIni].dist=0;
    //Ajusto valores al vertice inicial
     for ( i = 0; i < G->orden; i++)
    {
        vAct=obtenerVDistMinNoAlcanzado(G);
        G->directorio[vAct].alcanzado=1;
        aux = G->directorio[vAct].listaAdyacencia;
        // ALcanzo al vertice adyacente cuya arista sea la de menor peso 
        while (aux!= NULL)
        {
            distNueva = G->directorio[vAct].dist + aux->coste;
            if (distNueva < G->directorio[aux->idV].dist)
            {
                 G->directorio[aux->idV].dist=distNueva;
                 G->directorio[aux->idV].ant=vAct;
            }
            aux=aux->sig;
        }    
    }
}

void DijkstraMont(tipoGrafo *G,int vIni){
    Monticulo M;
    tipoElementoD elem;
    int distNueva;
    tipoArco *aux;
    iniciarGrafo(G);
    G->directorio[vIni].ant=-1;
    G->directorio[vIni].dist=0;
    iniciarMonticulo(&M);
    //Asigno valores iniciales a vIni
    elem.coste=0;
    elem.idV1=vIni;
    insertar(&M,elem);
    while(!vacio(&M)){
        elem =eliminar(&M);
        if (G->directorio[elem.idV1].alcanzado==0)
        {
            G->directorio[elem.idV1].alcanzado=1;
            aux = G->directorio[elem.idV1].listaAdyacencia;
            while (aux!=NULL)
            {
                distNueva=G->directorio[aux->idV].dist + aux->coste;
                if (distNueva < G->directorio[aux->idV].dist)
                {
                    G->directorio[aux->idV].dist=distNueva;
                    G->directorio[aux->idV].ant=elem.idV1;
                    elem.coste=distNueva;
                    elem.idV=aux->idV;
                    insertar(&M,elem);
                }
                aux=aux->sig;
            }
            
        }
        
    }
}