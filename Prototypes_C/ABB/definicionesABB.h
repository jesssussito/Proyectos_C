#include <stdio.h>
#include <stdlib.h>

typedef int tipoInfo;
typedef struct nodo{
    tipoInfo info;
    int fe;
    struct nodo *izq, *der;
} tipoNodo;
typedef tipoNodo *Arbol;
typedef Arbol *ArbolRef;


void insertarABBB(Arbolref *raiz, tipoInfo info, int *CAMBIA_H) {
    tipoNodo *nuevo, *nodo, *nodo1, *nodo2;

    /* Caso base: nodo vacío */
    if (*raiz == NULL) {
        nuevo = malloc(sizeof(tipoNodo));
        if (nuevo == NULL) {
            fprintf(stderr, "Error de malloc\n");
            exit(EXIT_FAILURE);
        }
        nuevo->info = info;
        nuevo->izq  = nuevo->der = NULL;
        nuevo->fe   = 0;
        *raiz       = nuevo;
        *CAMBIA_H   = 1;
        return;
    }

    /* Inserción en subárbol izquierdo */
    if (info < (*raiz)->info) {
        insertarABBB(&(*raiz)->izq, info, CAMBIA_H);
        if (*CAMBIA_H) {
            if ((*raiz)->fe == 1) {
                /* Antes estaba derecho más alto, al crecer izquierda queda balanceado */
                (*raiz)->fe = 0;
                *CAMBIA_H = 0;
            }
            else if ((*raiz)->fe == 0) {
                /* Antes balanceado, ahora izquierda más alto */
                (*raiz)->fe = -1;
                /* CAMBIA_H sigue valiendo 1 */
            }
            else {
                /* fe == -1: desbalance por exceso en izquierda → rotaciones */
                nodo  = *raiz;
                nodo1 = nodo->izq;
                if (nodo1->fe == -1) {
                    /* Caso II: rotación simple derecha */
                    nodo->izq    = nodo1->der;
                    nodo1->der   = nodo;
                    nodo->fe     = 0;
                    nodo1->fe    = 0;
                    *raiz        = nodo1;
                } else {
                    /* Caso ID: rotación doble (izq–der) */
                    nodo2           = nodo1->der;
                    nodo1->der      = nodo2->izq;
                    nodo->izq       = nodo2->der;
                    nodo2->izq      = nodo1;
                    nodo2->der      = nodo;
                    /* Ajuste de factores según fe de nodo2 */
                    if (nodo2->fe == -1) {
                        nodo1->fe = 0;
                        nodo->fe  = 1;
                    }
                    else if (nodo2->fe == 0) {
                        nodo1->fe = 0;
                        nodo->fe  = 0;
                    }
                    else { /* nodo2->fe == 1 */
                        nodo1->fe = -1;
                        nodo->fe  = 0;
                    }
                    nodo2->fe   = 0;
                    *raiz       = nodo2;
                }
                *CAMBIA_H = 0;
            }
        }
    }
    /* Inserción en subárbol derecho (rama nueva) */
    else if (info > (*raiz)->info) {
        insertarABBB(&(*raiz)->der, info, CAMBIA_H);
        if (*CAMBIA_H) {
            if ((*raiz)->fe == -1) {
                /* Antes estaba izquierdo más alto, al crecer derecha queda balanceado */
                (*raiz)->fe = 0;
                *CAMBIA_H = 0;
            }
            else if ((*raiz)->fe == 0) {
                /* Antes balanceado, ahora derecha más alto */
                (*raiz)->fe = 1;
                /* CAMBIA_H sigue valiendo 1 */
            }
            else {
                /* fe == 1: desbalance por exceso en derecha → rotaciones */
                nodo  = *raiz;
                nodo1 = nodo->der;
                if (nodo1->fe == 1) {
                    /* Caso DD: rotación simple izquierda */
                    nodo->der    = nodo1->izq;
                    nodo1->izq   = nodo;
                    nodo->fe     = 0;
                    nodo1->fe    = 0;
                    *raiz        = nodo1;
                } else {
                    /* Caso DI: rotación doble (der–izq) */
                    nodo2           = nodo1->izq;
                    nodo1->izq      = nodo2->der;
                    nodo->der       = nodo2->izq;
                    nodo2->der      = nodo1;
                    nodo2->izq      = nodo;
                    /* Ajuste de factores según fe de nodo2 */
                    if (nodo2->fe == 1) {
                        nodo->fe   = 0;
                        nodo1->fe  = -1;
                    }
                    else if (nodo2->fe == 0) {
                        nodo->fe   = 0;
                        nodo1->fe  = 0;
                    }
                    else { /* nodo2->fe == -1 */
                        nodo->fe   = 1;
                        nodo1->fe  = 0;
                    }
                    nodo2->fe   = 0;
                    *raiz       = nodo2;
                }
                *CAMBIA_H = 0;
            }
        }
    }
    else {
        /* info == (*raiz)->info: ya existe, no cambiamos altura */
        *CAMBIA_H = 0;
    }
}
