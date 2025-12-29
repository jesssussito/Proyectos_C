#include "prototiposM.h"

void inicarM(Monticulo *m){
    m->tam=0;
}
void ordenar(Monticulo *M){
    int i;
    for (i=M->tam/2;i>=1;i--)
    {
        filtradoDesc(M,i);
    }
    
}
tipoElemento eliminarMin(Monticulo *M,int indice){
    tipoElemento min;
    if (M->tam == 0)
    {
        //error a especificacion
    }else{
        min = M->elemento[indice];
        M->elemento[indice]=M->elemento[M->tam];
        M->tam--;
        filtradoDesc(M,indice);
        return min;
    } 
}
//Ordenacion por Monticulo
void heapShort(int *T,int n){
    Monticulo M;
    int i;
    for ( i = 0; i < n; i++)
    {
        insertar(&M,T[i]);
    }
    for ( i = 0; i < n; i++)
    {
        T[i]=eliminarMin(&M,i);
    }
    
    
}

//FILTRADOS
void filtradoDescendente(Monticulo *M,int indice){
    int fin,temp,hijoI,hijoD,hijoM;
    fin=0;
    while (!fin)
    {
        hijoI=indice*2;
        hijoD=(indice*2)+1;
        if (hijoI>M->tam)
        {
            fin=1;
        }else{
            hijoM=hijoI;
            if (hijoD <= M->tam && M->elemento[hijoD] < M->elemento[hijoI])
            {
                hijoM=hijoD;
            }
            if (M->elemento[hijoM]<M->elemento[indice])
            {   
                fin=1;
            }else{
                temp=M->elemento[hijoD];
                M->elemento[hijoD]=M->elemento[indice];
                M->elemento[indice]=temp;
                indice=hijoM;
            }           
        }       
    }  
}
void filtradoAscendente(Monticulo *M,tipoElemento x){
    int act,padre,fin;
    tipoElemento temp;
    if (M->tam +1 >= TAM)
    {
        //error a especificaion
    }else{
        M->tam++;
        M->elemento[M->tam]=x;
        act=M->tam;
        fin=0;
        while (!fin)
        {
            padre=act/2;
            if (padre==0 || M->elemento[padre]<M->elemento[act])
            {
                fin=1;
            }else{
                temp=M->elemento[padre];
                M->elemento[padre]=M->elemento[act];
                M->elemento[act]=temp;
                act=padre;
            }
            
        }
        
    }
    
}