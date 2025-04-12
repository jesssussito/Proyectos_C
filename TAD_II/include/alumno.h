#include <stdlib.h>
#ifndef __ALUMNO_H
#define __ALUMNO_H
#define C 8	// Capacidad del cubo fichero de alumnos
typedef struct {
	char dni[9];		// campo clave
	char nombre[19];
	char ape1[19];
	char ape2[19];
	char provincia[11];
	} tAlumno;
int funcionHash(tAlumno *reg,int nCubos){
	return atoi(reg->dni)%nCubos;
}	
void mostrarReg(tAlumno *reg);
int cmpClave(tAlumno *reg1, tAlumno *reg2){
	if (strcmp(reg1->dni,reg2->dni)==0)
	{
		return 1;
	}else{
		return 0;
	}
	
}
int buscar(char *fichero, char *dni);
int modificar(char *fichero, char *dni,char *provincia){
	tAlumno reg;
	strcpy(reg->dni,dni);
	busquedaHash(fHash,&reg,&posicion);
	strcpy(reg->provincia,provincia)
	modificarReg(fHash,&reg,&posicion);
}
#endif
