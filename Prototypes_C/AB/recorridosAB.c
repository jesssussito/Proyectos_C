#include <stdio.h>
#include <stdlib.h>
#include "prototipoAB.h"

void Amplitud(Arbol *raiz){
    Cola c;
    tipoNodo act;
    inicializarCola(&c);
    if(raiz != NULL){
        insertarCola(&c,raiz);
        while(!vacia(&c)){
            act=suprimeCola(&c);
            visitar(act);
            if (act->izq != NULL)
            {
                insertarCola(&c,act->izq);
            }else if (act->der!=NULL)
            {
                insertarCola(&c,act->der);
            }
            
            
        }
    }
}
void Ordenes(Arbol *raiz){
    if (raiz!=NULL)
    {
        visitar(raiz);
        Ordenes(raiz->izq);     //Pivotando obtengo diferentes ordenes
        Ordenes(raiz->der);
    }
    
}

int calcularABAlg(Arbol *raiz){
    int res,varI,varD;
    res=0;
    if (raiz!=NULL)
    {
        if (raiz->izq == NULL && raiz->der == NULL)
        {
            res=raiz->info;// si raiz->info es un Char entonces se hace -'0'
        }
        varI=calcularABAlg(raiz->izq);
        varD=calcularABAlg(raiz->der);
        switch (raiz->info)
        {
        case 1:
            //aqui ya lo que me pidan
            break;
        
        default:
            break;
        }
    }
    
}

