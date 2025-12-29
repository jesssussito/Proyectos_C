#ifndef __SECUENCIAL_H
#define __SECUENCIAL_H

#include <stdio.h>
#include "alumno.h"    /* trae tAlumno y mostrarReg() */

int leeSecuencial(char *fichero);
int buscaReg(FILE *fSecuencial, tAlumno *reg, char *dni);
int insertaReg(char *fSecuencial, tAlumno *reg);

#endif
