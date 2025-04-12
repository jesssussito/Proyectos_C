#include "ejercicio2.h"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main() {
	 int i,numRegDes;
	 FILE *f;
	 tipoAlumno reg;
	 char dni[10];

	  numRegDes=creaHash("alumnos.dat","alumnos.hash");
	  printf("%d Registros DESBORDADOS\n\n",numRegDes);

	  // B�squeda de registros
	  f=fopen("alumnos.hash","rb");

	  printf("PRUEBAS EJERCICIO 2\n\n");

	  // Primera prueba
	  strcpy(dni,"15838332");
	  printf("PRIMERA PRUEBA CON DNI %s\n",dni);
	  i = modificarReg("alumnos.hash", dni, "SEVILLA");
	  if (i < 0) {
	  	printf(" - Error al modificar el alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro modificado correctamente\n");
	  }

	  i = buscaReg(f,&reg,dni);
	  if (i < 0) {
	  	printf(" - No existe alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro encontrado en el CUBO %d\n",i);
	  	printf(" - Registro modificado -> %s %s %s %s %s\n\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
	  }

	  // Segunda Prueba
	  strcpy(dni,"6883822");
	  printf("SEGUNDA PRUEBA CON DNI %s\n",dni);
	  i = modificarReg("alumnos.hash", dni, "SEVILLA");
	  if (i < 0) {
	  	printf(" - Error al modificar el alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro modificado correctamente\n");
	  }

	  i = buscaReg(f,&reg,dni);
	  if (i < 0) {
	  	printf(" - No existe alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro encontrado en el CUBO %d\n",i);
	  	printf(" - Registro modificado -> %s %s %s %s %s\n\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
	  }

	  // Tercera Prueba
	  strcpy(dni,"7282323");
	  printf("TERCERA PRUEBA CON DNI %s\n",dni);
	  i = modificarReg("alumnos.hash", dni, "SEVILLA");
	  if (i < 0) {
	  	printf(" - Error al modificar el alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro modificado correctamente\n");
	  }

	  i = buscaReg(f,&reg,dni);
	  if (i < 0) {
	  	printf(" - No existe alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro encontrado en el CUBO %d\n",i);
	  	printf(" - Registro modificado -> %s %s %s %s %s\n\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
	  }

	  // Cuarta Prueba
	  strcpy(dni,"7219752");
	  printf("CUARTA PRUEBA CON DNI %s\n",dni);
	  i = modificarReg("alumnos.hash", dni, "SEVILLA");
	  if (i < 0) {
	  	printf(" - Error al modificar el alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro modificado correctamente\n");
	  }

	  i = buscaReg(f,&reg,dni);
	  if (i < 0) {
	  	printf(" - No existe alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro encontrado en el CUBO %d\n",i);
	  	printf(" - Registro modificado -> %s %s %s %s %s\n\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
	  }


	  // Quinta Prueba
	  strcpy(dni,"9389298");
	  printf("QUINTA PRUEBA CON DNI %s\n",dni);
	  i = modificarReg("alumnos.hash", dni, "SEVILLA");
	  if (i < 0) {
	  	printf(" - Error al modificar el alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro modificado correctamente\n");
	  }

	  i = buscaReg(f,&reg,dni);
	  if (i < 0) {
	  	printf(" - No existe alumno con dni %s\n",dni);
	  } else { 
		printf(" - Registro encontrado en el CUBO %d\n",i);
	  	printf(" - Registro modificado -> %s %s %s %s %s\n\n",reg.dni,reg.nombre,reg.ape1,reg.ape2,reg.provincia);
	  }
	  fclose(f);
	  //Fin de B�squeda
}




