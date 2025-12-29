#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dispersion.h"
#include "alumno.h"
int funcionHash(tAlumno *reg,int nCubos){
	return atoi(reg->dni)%nCubos;
}	
void mostrarReg(tAlumno *reg){
	printf("DNI: %s\n",    reg->dni);
    printf("Nombre: %s\n", reg->nombre);
    printf("1º Apellido: %s\n", reg->ape1);
    printf("2º Apellido: %s\n", reg->ape2);
    printf("Provincia: %s\n",   reg->provincia);
}
int cmpClave(tAlumno *reg1, tAlumno *reg2){
	if (strcmp(reg1->dni,reg2->dni)==0)
	{
		return 1;
	}else{  
		return 0;
	}
	
}
int buscar(char *fichero,char *dni){
    int c;
    tAlumno reg;
    tPosicion pos;
    FILE *f = fopen(fichero,"r+b");
    if (f==NULL)
    {
        return -1;
    }
    strcpy(reg.dni,dni);
    c=buscarReg(f,(tipoReg*)&reg,&pos);
    if (c>=0)
    {
        mostrarReg(&reg);
    }
    fclose(f);
    return c;
}
int modificar(char *fichero, char *dni,char *provincia){
    tAlumno reg;
    tPosicion pos;
    int res,c;
    FILE *f = fopen(fichero,"r+b");
    if (f==NULL)
    {
        return -1;
    }
    strcpy(reg.dni,dni);
    c=buscarReg(f,(tipoReg*)&reg,&pos);
    if (c<0)
    {
        fclose(f);
        return -1;
    }
    strcpy(reg.provincia,provincia);
    res = modificarReg(f,(tipoReg*)&reg,&pos);
    fclose(f);
    return (res >= 0) ? c : -1;
}
