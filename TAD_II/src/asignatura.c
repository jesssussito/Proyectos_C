#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dispersion.h"
#include "asignatura.h"
int buscar(char *fichero, int codigo){
    tAsignatura reg;
    int c;
    FILE *f = fopen(fichero,"r+b");
    if (f==NULL)
    {
        return -1;
    }
    reg.codigo=codigo;
    c=buscarReg(f,(tipoReg*)&reg,(char*)&codigo);
    if (c>=0)
    {
        mostrarReg(&reg);
    }
    fclose(f);
    return c; 
}
int modificar(char *fichero, int codigo,float creditosT, float creditosP){
    int c,res;
    tAsignatura reg;
    tPosicion pos;
    FILE *f = fopen(fichero,"r+b");
    if (f==NULL)
    {
        return -1;
    }
    reg.codigo=codigo;
    c=buscarReg(f,(tipoReg*)&reg,(char*)&codigo);
    if (c<0)
    {
        fclose(f);
        return -1;
    }
    reg.creditosP=creditosP;
    reg.creditosT=creditosT;
    res = modificarReg(f,(tipoReg*)&reg,&pos);
    fclose(f);
    return res >=0 ? c : -1;
}
int funcionHash(tAsignatura *reg,int nCubos){
	return reg->codigo%nCubos;
}
void mostrarReg(tAsignatura *reg){
	printf("=== Asignatura ===\n");
    printf("Código:      %d\n", reg->codigo);
    printf("Nombre:      %s\n", reg->nombre);
    printf("Curso:       %c\n", reg->curso);
    printf("Créd. Teoría: %.2f\n", reg->creditosT);
    printf("Créd. Práct.: %.2f\n", reg->creditosP);
    printf("Tipo:        %c\n", reg->tipo);
    printf("Cuatrimestre:%c\n", reg->cuatrimestre);
    printf("Grupos T:    %d\n", reg->numGrT);
    printf("Grupos P:    %d\n", reg->numGrP);
    printf("===================\n");
}
int cmpClave(tAsignatura *reg1, tAsignatura *reg2){
	if (reg1->codigo==reg2->codigo)
	{
		return 1;
	}else{
		return 0;
	}
	
}