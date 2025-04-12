#include "ejercicio1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	 int i,numReg;
	 FILE *f;
	 tipoAlumno reg;
	 tipoArbolBB a = NULL;

	  numReg=genABB("alumnos.dat", &a);
	  printf("Numero de Registros de apellidos diferentes: %d \n\n",numReg);
	  enOrden(a);

	  //Fin de B�squeda
}


