#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lista.h"
int purga(Lista *l);

int
main(void)
{
    Lista miListaA,miListaB;
    tipoPosicion p;
    int i;
    tipoElemento v[]={45,25,45,50,60,50};
    int n =sizeof(v)/sizeof(tipoElemento);

    printf("Creando listaA vacía: %d\n", creaVacia(&miListaA));

    p = primero(&miListaA);
    for (i = 0; i < n; i++) {
        inserta(v[i],p,&miListaA);
        p = siguiente(p,&miListaA);
    }
    imprime(&miListaA);
    printf("Eliminando repetidos \n");
    purga(&miListaA);
    imprime(&miListaA);

    printf("Creando listaB vacía: %d\n", creaVacia(&miListaB));

    for (i = n-1; i >= 0; i--) {
        inserta(v[i],fin(&miListaB),&miListaB);
    }
    imprime(&miListaB);
    
	
	printf("\nAhora concateno: (%d)\n", concatena(&miListaA, &miListaB));
	imprime(&miListaA);
	imprime(&miListaB);
	
	
    anula(&miListaA);
    destruye(&miListaA);
    
    anula(&miListaB);
    destruye(&miListaB);
	
    return 0;
}

int
purga(Lista *l)
{
    tipoPosicion act, sig;
    
    act = primero(l);
    while (act != fin(l)) {
        sig = siguiente(act,l);
        while (sig != fin(l)) {
            if (recupera(act,l) == recupera(sig,l))
                suprime(sig, l);
            else
                sig = siguiente(sig,l);
        }
        act = siguiente(act,l);
    }
    return 0;
}


