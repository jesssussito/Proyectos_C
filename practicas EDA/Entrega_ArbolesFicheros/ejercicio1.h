#ifndef __EJERCICIO1_H
#define __EJERCICIO1_H 

	typedef struct {
		char dni[9];
		char nombre[19];
		char ape1[19];
		char ape2[19];
		char provincia[11];
	} tipoAlumno;

	typedef int tipoInfo;
	typedef char tipoClave[20];

	typedef struct tipoNodo {
	        tipoClave clave;
			tipoInfo info;
	        struct tipoNodo *izq,*der;
	} tipoNodo;

	typedef tipoNodo *tipoArbolBB;

	int genABB(char *ficheroDatos, tipoArbolBB *arbol);
	int insertar(tipoArbolBB *arbol,tipoClave alumno);
	void enOrden(tipoArbolBB a);
	
#endif

