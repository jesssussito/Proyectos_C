#include "definiciones.h"


void amplitudG(tipoGrafo *G, int vIni){
    Cola c;
    int idVsig;
    tipoArco *aux;
    iniciar(&c);
    encolar(&c,vIni);
    while(!vacia(&c)){
        idVsig = desencolar(&c);
        if (G->directorio[idVsig].alcanzado == 0)
        {
            visitar(G,idVsig);
            G->directorio[idVsig].alcanzado=1;
            aux = G->directorio[idVsig].listaAdyacencia;
            while (aux != NULL)
            {
                encolar(&c,aux->idV);
                aux=aux->sig;
            }           
        }      
    }
}
//En caso de que haya componentes no accesibles desde vIni
void amplitudGExt(tipoGrafo *G, int vIni){
    int i;
    amplitudG(G,vIni);
    for ( i = 0; i < G->orden; i++)
    {
        if (G->directorio[i].alcanzado == 0)
        {
            amplitud(G,i);
        }       
    }   
}
void profundidadG(tipoGrafo *G, int vAct){
    tipoArco *aux;
    if (G->directorio[vAct].alcanzado==0)
    {
        visitar(G,vAct);
        G->directorio[vAct].alcanzado=1;
        aux=G->directorio[vAct].listaAdyacencia;
        while(aux != NULL){
            profundidad(G,aux->idV);
            aux=aux->sig;
        }
    }
}
void profundidadGExt(tipoGrafo *G, int vAct){
    int i;
    profundidadG(G,vAct);
    for ( i = 0; i < G->orden; i++)
    {
        if (G->directorio[i].alcanzado==0)
        {
            profundidadG(G,i);
        }   
    }  
}