#ifndef __CONJUNTOS_A_H
#define __CONJUNTOS_A_H

#define MAX 16

typedef int particion[MAX];
typedef int tipoConjunto;
typedef int tipoElementoCon;

// Funciones a implementar

// 1. Las tres básicas
void crea(particion P);
tipoConjunto buscar(tipoElementoCon x, particion P);
void unir(tipoConjunto x, tipoConjunto y, particion P);

// 2. Implementación con control de representantes: Si x e y son los representantes de sus clases de equivalencia las unen y devuelven VERDADERO, en otro caso no hace nada y devuelve FALSO
int unir1(tipoConjunto x, tipoConjunto y, particion P);

// 3. Versión de buscar con Compresión de Caminos
tipoConjunto buscarCC(tipoElementoCon x, particion P);

// Función proporcionada
void verParticion(particion P);
#endif

