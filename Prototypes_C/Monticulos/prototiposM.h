#define TAM 100
typedef int tipoElemento;
typedef struct{
    tipoElemento elemento[TAM];
    int tam;
}Monticulo;

void inicarM(Monticulo *m);
void ordenar(Monticulo *M);
tipoElemento eliminar(Monticulo *m,int indice);
void filtradoDescendente(Monticulo *M,int indice);
void filtradoAcendente(Monticulo *M, tipoElemento x);
void heapShort(int *T,int n);