#include "ejercicio2.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void creaHvacio(char *fichHash) { 
  FILE *fHash;
  tipoCubo cubo;
  int j;
  int numCubos = CUBOS + CUBOSDESBORDE;

  memset(&cubo,0,sizeof(cubo));

  fHash = fopen(fichHash,"wb");
  for (j=0;j<numCubos;j++) fwrite(&cubo,sizeof(cubo),1,fHash);
  fclose(fHash);
}


int leeHash(char *fichHash) {
  FILE *f;
  tipoCubo cubo;
  int j,i=0;
  size_t numLee;

   f = fopen(fichHash,"rb");
   rewind(f);
   fread(&cubo,sizeof(cubo),1,f);
   while (!feof(f)){
	for (j=0;j<C;j++) {
        if (j==0)    	printf("Cubo %2d (%2d reg. ASIGNADOS)",i,cubo.numRegAsignados);
        else  	printf("\t\t\t");
	if (j < cubo.numRegAsignados) 
		    printf("\t%s %s %s %s %s\n",
	    		cubo.reg[j].dni,
			cubo.reg[j].nombre,
			cubo.reg[j].ape1,
		  	cubo.reg[j].ape2,
  	                cubo.reg[j].provincia);
	else printf ("\n");
        }
       i++;
       fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   return i;
}


int creaHash(char *fichEntrada,char *fichHash) {
	FILE *f,*f2;
	tipoAlumno alumno;
    tipoCubo cubo;
	int numCubo, i = 0, numRegDesbordados = 0, j = 0;

	creaHvacio(fichHash);
	
	f = fopen(fichEntrada,"rb");
	rewind(f);
	fread(&alumno,sizeof(alumno),1,f);

    f2 = fopen(fichHash,"r+");
   	rewind(f2);

	while (!feof(f)) {
		i = 0;
		j = 0;

		numCubo = atoi(alumno.dni) % CUBOS;
		
		fseek(f2, numCubo*sizeof(tipoCubo), SEEK_SET);
		fread(&cubo,sizeof(tipoCubo),1,f2);

		if(cubo.numRegAsignados < C) {
			// Insertar en area normal
			cubo.reg[cubo.numRegAsignados] = alumno; 
			cubo.numRegAsignados++;
			i = 1; 
			fseek(f2, numCubo*sizeof(tipoCubo), SEEK_SET);
			fwrite(&cubo,sizeof(char),sizeof(tipoCubo),f2);	
		} else {
			// Insertar en el area de desborde
			cubo.numRegAsignados++;  // Se modifica el numero de asignados cuando se produce desborde y se escribe en el fichero
			fseek(f2, numCubo*sizeof(tipoCubo), SEEK_SET);
			fwrite(&cubo,sizeof(char),sizeof(tipoCubo),f2);	

			while (!feof(f2) && i != 1) {
				fseek(f2, (CUBOS+j)*sizeof(tipoCubo), SEEK_SET); // Se coloca el fichero en el area de desborde
				fread(&cubo,sizeof(tipoCubo),1,f2);

				if(cubo.numRegAsignados < C) {			
					cubo.reg[cubo.numRegAsignados] = alumno;
					cubo.numRegAsignados++;
					i = 1; 

					fseek(f2, (CUBOS+j)*sizeof(tipoCubo), SEEK_SET);
					fwrite(&cubo,sizeof(char),sizeof(tipoCubo),f2);	
				} else {
					cubo.numRegAsignados++;  // Se modifica el numero de asignados cuando se produce desborde y se escribe en el fichero
					fseek(f2, (CUBOS+j)*sizeof(tipoCubo), SEEK_SET);
					fwrite(&cubo,sizeof(char),sizeof(tipoCubo),f2);	
				}
				j++;
			}

			if (i == 0) {
				fclose(f);
				fclose(f2);
				return -1; 
			}

			numRegDesbordados++;									
		}
	
		fread(&alumno,sizeof(alumno),1,f);
	}
	
	fclose(f);
	fclose(f2);
	return numRegDesbordados;
}



int buscaReg(FILE *fHash, tipoAlumno *reg,char *dni) {
	int numCubo, j, i = 0;	
	tipoCubo cubo;

   	rewind(fHash);
	fread(&cubo,sizeof(tipoCubo),1,fHash);

	numCubo = atoi(dni) % CUBOS;

	fseek(fHash, (numCubo)*sizeof(tipoCubo), SEEK_SET);
	fread(&cubo,sizeof(tipoCubo),1,fHash);

	for (j = 0; j < C; j++) { // Se busca si el registro esta en el cubo que le corresponde
		if (strcmp(cubo.reg[j].dni, dni) == 0) {
			*reg = cubo.reg[j];
			return numCubo;
		}
	}

		
	if(cubo.numRegAsignados > C) { // Si el cubo tiene mas registro (hay registros en el area de desborde)
		fseek(fHash, CUBOS*sizeof(tipoCubo), SEEK_SET); // Se coloca el fichero en el area de desborde
		fread(&cubo,sizeof(tipoCubo),1,fHash);

		while (!feof(fHash)){
			for (j = 0; j < C; j++) {
				if (strcmp(cubo.reg[j].dni, dni) == 0) {
					*reg = cubo.reg[j];
					return CUBOS+i;
				}
			}
			i++;
			fread(&cubo,sizeof(tipoCubo),1,fHash);
		}
	}

    return -1; 
}


int modificarReg(char *fichero, char *dni, char *provincia) {
	FILE *f2;
	int numCubo,i;	
	tipoAlumno reg;
	tipoCubo cubo;

	f2 = fopen(fichero,"r+");
   	rewind(f2);

	numCubo = buscaReg(f2,&reg,dni);
	if (numCubo == -1) {
		return -1;
	}


	fseek(f2, (numCubo)*sizeof(tipoCubo), SEEK_SET);
	fread(&cubo,sizeof(tipoCubo),1,f2);
	
	for (i = 0; i < C; i++) { 
		if (strcmp(cubo.reg[i].dni, dni) == 0) {

			strcpy(cubo.reg[i].provincia, provincia);

			fseek(f2, (numCubo)*sizeof(tipoCubo), SEEK_SET);
			fwrite(&cubo,sizeof(char),sizeof(tipoCubo),f2);	

			fclose(f2);
			return numCubo;
		}
	}
	
	fclose(f2);
	return numCubo;
}


