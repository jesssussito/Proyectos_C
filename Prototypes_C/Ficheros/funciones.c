#include "../include/dispersion.h"
#include <asm-generic/errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXITO 0
#define ERROR_FICHERO_ENTRADA -1
#define REGISTRO_NO_ENCONTRADO -1
#define ERROR_FICHERO_SALIDA -2
#define ERROR_FICHERO -2
#define ERROR_SUPERADA_DENSIDAD_MAXIMA -3
#define ERROR_REDUCIDA_DENSIDAD_MINIMA -4
#define ERROR_PARAMETROS_ENTRADA -5

int creaHash(char *fichEntrada, char *fichHash, regConfig *regC) {
	// Validar parametros
	if (regC->nCubos < 8 || regC->nCubosDes < 4 || regC->densidadMax <= 0 || regC->densidadMin <= 0) {
		return ERROR_PARAMETROS_ENTRADA;
	}

	// Crear fichero hash
	if (creaHvacio(fichHash, regC) != 0) {
		return ERROR_FICHERO_SALIDA;
	}

	// Abrir fichero de entrada
	FILE *fIn = fopen(fichEntrada, "rb");
	if (fIn == NULL) {
		return ERROR_FICHERO_ENTRADA;
	}

	// Abrir fichero hash para lectura y escritura
	FILE *fHash = fopen(fichHash, "r+b");
	if (fHash == NULL) {
		fclose(fIn);
		return ERROR_FICHERO_SALIDA;
	}

	// Leer y insertar registros del fichero de entrada
	tipoReg reg;
	while (fread(&reg, sizeof(tipoReg), 1, fIn) == 1) {
		if (insertar(fHash, &reg, regC) != 0) {
			fclose(fIn);
			fclose(fHash);
			return ERROR_PARAMETROS_ENTRADA;
		}
	}

	// Posible error en lectura
	if (!feof(fIn)) {
		fclose(fIn);
		fclose(fHash);
		return ERROR_FICHERO_ENTRADA;
	}

	// Densidad de ocupacion
	float densidad = (float)regC->numReg / (regC->nCubos * C);

	// Actualizar configuracion
	fseek(fHash, 0, SEEK_SET);
	if (fwrite(regC, sizeof(regConfig), 1, fHash) != 1) {
		fclose(fIn);
		fclose(fHash);
		return ERROR_FICHERO_SALIDA;
	}

	fclose(fIn);
	fclose(fHash);

	return EXITO;
}

int creaHvacio(char *fichHash, regConfig *regC) {
	// Comprobar parametros
	if (regC->nCubos < 8 || regC->nCubosDes < 4 || regC->densidadMax <= 0 || regC->densidadMin <= 0) {
		return ERROR_PARAMETROS_ENTRADA;
	}

	FILE *f = fopen(fichHash, "wb");
	if (f == NULL) {
		return ERROR_FICHERO;
	}

	// Iniciar valores del registro de configuracion
	regC->numReg = 0;
	regC->numRegDes = 0;
	// Primer cubo de desborde
	regC->nCuboDesAct = regC->nCubos;

	// Escribir el registro de config
	if (fwrite(regC, sizeof(regConfig), 1, f) != 1) {
		fclose(f);
		return ERROR_FICHERO_SALIDA;
	}

	// Cubos principales
	tipoCubo cuboVacio;
	cuboVacio.numRegAsignados = 0;
	cuboVacio.desbordado = 0;
	for (int i = 0; i < regC->nCubos; i++) {
		if (fwrite(&cuboVacio, sizeof(tipoCubo),regC->nCubos, f) != 1) {
			fclose(f);
			return ERROR_FICHERO_SALIDA;
		}
	}

	// Cubos de desborde
	for (int i = 0; i < regC->nCubosDes; i++) {
		if (fwrite(&cuboVacio, sizeof(tipoCubo), 1, f) != 1) {
			fclose(f);
			return ERROR_FICHERO_SALIDA;
		}
	}

	fclose(f);
	return 0;
}



int insertar(FILE *fHash, tipoReg *reg, regConfig *regC) {
	// Calcular el cubo donde deberia de ir usando la funcion hash
	int cuboDestino = funcionHash(reg, regC->nCubos);

	// Posicionarse en el cubo donde deberia de ir
	long pos = sizeof(regConfig) + (cuboDestino * sizeof(tipoCubo));
	fseek(fHash, pos, SEEK_SET);

	// Leer el cubo
	tipoCubo cubo;
	if (fread(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
		return ERROR_FICHERO_SALIDA;
	}

	// Intentar insertar en el cubo que le toca si no esta lleno ( C: capacidad )
	if (cubo.numRegAsignados < C) {
		cubo.reg[cubo.numRegAsignados] = *reg;
		cubo.numRegAsignados++;

		// Actualizar el cubo escribiendolo
		fseek(fHash, pos, SEEK_SET);
		if (fwrite(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
			return ERROR_FICHERO_SALIDA;
		}
	} else {
		// Si no se puede, el cubo esta lleno ,entonces se desborda
		if (!cubo.desbordado) {
			cubo.desbordado = 1;
			fseek(fHash, pos, SEEK_SET);
			if (fwrite(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
				return ERROR_FICHERO_SALIDA;
			}
		}

		// Insertar el registro en el area de desborde
		if (desborde(fHash, reg, regC) != 0) {
			return ERROR_FICHERO_SALIDA;
		}
	}

	// Actualizar registro de config
	regC->numReg++;

	return EXITO;
}
/// @brief ///////////////////
/// @param fHash 
/// @param reg 
/// @param regC 
/// @return /
int desborde(FILE *fHash, tipoReg *reg, regConfig *regC) {
	// Situarse en el cubo de desborde actual
	long pos = sizeof(regConfig) + (regC->nCuboDesAct * sizeof(tipoCubo));
	fseek(fHash, pos, SEEK_SET);

	// Leer el cubo de desborde
	tipoCubo cubo;
	if (fread(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
		return ERROR_FICHERO_SALIDA;
	}

	// Insertar registro en el cubo
	if (cubo.numRegAsignados < C) {
		cubo.reg[cubo.numRegAsignados] = *reg;
		cubo.numRegAsignados++;
	} else {
		// Se lleno, avanzamos al siguiente
		regC->nCuboDesAct++;

		// Si nos hemos quedado sin cubos, creamos otro
		if (regC->nCuboDesAct >= (regC->nCubos + regC->nCubosDes)) {
			tipoCubo nuevoCubo;
			nuevoCubo.numRegAsignados = 0;
			nuevoCubo.desbordado = 0;
            
			fseek(fHash, 0, SEEK_END);
			if (fwrite(&nuevoCubo, sizeof(tipoCubo), 1, fHash) != 1) {
				return ERROR_FICHERO_SALIDA;
			}

			regC->nCubosDes++;
		}

		// Volver a intentar insertarlo en el nuevo cubo
		return desborde(fHash, reg, regC);
	}

	// Actualizar el cubo en el fichero hash
	fseek(fHash, pos, SEEK_SET);
	if (fwrite(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
		return ERROR_FICHERO_SALIDA;
	}

	// Actualizar registro de config
	regC->numRegDes++;

	return EXITO;
}
/// @brief ////////////
/// @param fHash 
/// @param reg 
/// @param posicion 
/// @return 
int busquedaHash(FILE *fHash, tipoReg *reg, tPosicion *posicion) {
	//Comprobacion de parametros
	if (fHash == NULL || reg == NULL || posicion == NULL) {
		return -5;
	}

	regConfig config;
	fseek(fHash, 0, SEEK_SET);
	if (fread(&config, sizeof(regConfig), 1, fHash) != 1) {
		return -2;
	}
    // He leido el archivo y ahora se el numCubos,numCubosDesborde y numCubosDesbordeAct

	// Calcular cubo principal usando la función hash
	posicion->cubo = funcionHash(reg, config.nCubos);
	posicion->cuboDes = -1;
	posicion->posReg = -1;

	// Posicionarnos en el cubo principal & leer
	fseek(fHash, sizeof(regConfig) + (posicion->cubo * sizeof(tipoCubo)), SEEK_SET);

	tipoCubo cubo;
	if (fread(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
		return -2;
	}
    // Leo el cubo 

	// Buscar en el cubo principal en los cubos Normales
	for (int i = 0; i < cubo.numRegAsignados; i++) {
		if (cmpClave(&cubo.reg[i], reg) == 0) {
			// Registro encontrado en cubo principal
			*reg = cubo.reg[i];
			posicion->posReg = i;//sI ES UN INT cuboDest * C +1
			return 0;
		}
	}

	// Si no está en el cubo principal pero esta desbordado, buscar en area desborde
	if (cubo.desbordado) {
		// Buscar en todos los cubos de desborde
		for (int cuboDes = config.nCubos; cuboDes < config.nCubos + config.nCubosDes; cuboDes++) {
			fseek(fHash, sizeof(regConfig) + (cuboDes * sizeof(tipoCubo)), SEEK_SET);
			if (fread(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
				return -2;
			}

			for (int i = 0; i < cubo.numRegAsignados; i++) {
				if (cmpClave(&cubo.reg[i], reg) == 0) {
					// Encontrado en area de desborde
					*reg = cubo.reg[i];
					posicion->cuboDes = cuboDes;
					posicion->posReg = i;
					return 0;
				}
			}
		}
	}

	return -1;
}
 
int modificarReg(FILE *fHash, tipoReg *reg, tPosicion *posicion) {
	if (fHash == NULL || reg == NULL) {
		return -5;
	}

	// Primero buscar el registro si no nos han pasado la posicion
	tPosicion pos;
	if (posicion == NULL) {
		tipoReg regBusqueda = *reg;
		int resultado = busquedaHash(fHash, &regBusqueda, &pos);

		if (resultado != 0) {
			return resultado;
		}
		posicion = &pos;
	}

	long posicionArchivo;
	if (posicion->cuboDes == -1) {
		// Esta cubo principal
		posicionArchivo = sizeof(regConfig) + (posicion->cubo * sizeof(tipoCubo));
	} else {
		// Esta en cubo de desborde
		posicionArchivo = sizeof(regConfig) + (posicion->cuboDes * sizeof(tipoCubo));
	}

	// Leer el cubo
	fseek(fHash, posicionArchivo, SEEK_SET);
	tipoCubo cubo;
	if (fread(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
		return -2;
	}

	// Comprobar que no se ha movido
	if (cmpClave(&cubo.reg[posicion->posReg], reg) != 0) {
		return -5;
	}

	// Modificar el registro
	cubo.reg[posicion->posReg] = *reg;
	fseek(fHash, posicionArchivo, SEEK_SET);
	if (fwrite(&cubo, sizeof(tipoCubo), 1, fHash) != 1) {
		return -2;
	}

	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
//Si no me dan fichero ni regconfig
FILE *f= fopen("ruta.txt","r+b");//para buscar rb, para modificar/insertar r+b
if (f==NULL)
{
	//Error
}
regConfig regC;
fread(&regC,sizeof(regConfig),1,f);
tipoCubo cubo;
int cubodest = atoi(dni)%regC.nCubos;

