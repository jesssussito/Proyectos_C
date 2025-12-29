#include "definiciones.h"

int obtenerVsinOrdenEnt(tipoGrafo *G){
    int i;
    for ( i = 0; i < G->orden; i++)
    {
        if (G->directorio[i].ordenTopo== -1 && G->directorio[i].gradoEnt==0)
        {
            return i;
        }
    }
    return -1;
}
void ordenTopolog(tipoGrafo *G){
    int vAct,ordenT;
    tipoArco *aux;
    iniciarGrafo(G);
    for (ordenT = 1;ordenT < G->orden;ordenT++)
    {
        vAct=obtenerVsinOrdenEnt(G);
        if (vAct == -1)
        {
            //error el grafo tiene ciclos
        }
        G->directorio[vAct].ordenTopo=ordenT;
        aux = G->directorio[vAct].listaAdyacencia;
        while (aux != NULL)
        {
            G->directorio[aux->idV].gradoEnt--;
            aux = aux->sig;
        }        
    }   
}
void ordenTopologCola(tipoGrafo *G){
    Cola c;
    int i,vAct;
    tipoArco *aux;
    iniciarGrafo(G);
    iniciar(&c);
    //Todos los vertices cpn grado de entrada 0 se meten a la cola, ya que no tienen restriccion de vertice que le dirija
    for ( i = 0; i < G->orden; i++)
    {
        if (G->directorio[i].gradoEnt == 0 )
        {
            encolar(&c,i);
        }
    }
    i=1;
    //Proceso los nodos de la cola
    while (!vacia(&c))
    {
        vAct = suprime(&c);
        G->directorio[vAct].ordenTopo=i;
        //Saco de la cola y le asigno el orden
        i++;
        //Actualizo el G.Entrada de sus vecinos
        aux=G->directorio[vAct].listaAdyacencia;
        while (aux != NULL)
        {
            G->directorio[aux->idV].gradoEnt--;
            if (G->directorio[aux->idv].gradoEnt==0)
            {
                //Si ya no tiene restriccion de vertice que le dirija se mete a la cola
                insertar(&c,aux->idV);
            }
            aux=aux->sig;
        }
    }
    if (i<=G->orden)
    {
        // ERROR hay ciclos en G
    }
    
}