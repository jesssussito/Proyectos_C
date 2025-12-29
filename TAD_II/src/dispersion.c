#include "dispersion.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dispersion.h"

// Lee el contenido del fichero hash organizado mediante el método de DISPERSIÓN según los criterios
// especificados en la práctica. Se leen todos los cubos completos tengan registros asignados o no. La
// salida que produce esta función permite visualizar el método de DISPERSIÓN
int leeHash(char *fichHash)
{ FILE *f;
  tipoCubo cubo;
  regConfig regC;
  int j,nCubo=0,densidadOcupacion;
  
   if ((f = fopen(fichHash,"rb"))==NULL) return -2;
   if(fread(&regC,sizeof(regConfig),1,f)!=1){
      fclose(f);
      return -1;
   }
   if(fread(&cubo,sizeof(cubo),1,f)!=1){
      fclose(f);
      return -1;
   }
   while (!feof(f)){
      for (j=0;j<C;j++) {
            if (j==0)    	
               printf("Cubo %2d (%2d reg. ASIGNADOS)",nCubo,cubo.numRegAsignados);
            else 	if ((j==1) && cubo.desbordado) 
               printf("DESBORDADO\t\t");
            else 
               printf("\t\t\t");
            
            if (j < cubo.numRegAsignados) 
               mostrarReg(&(cubo.reg[j]));
            else 
               printf ("\n");
            }
         nCubo++;
         fread(&cubo,sizeof(cubo),1,f);
   }
   fclose(f);
   printf("ORGANIZACIÓN MÉTODO DISPERSIÓN:\n\t %d CUBOS y %d CUBOS DESBORDE con capacidad %d\n",
   		regC.nCubos,regC.nCubosDes, C);   
   printf("Cubo de Desborde Actual: %d\n", regC.nCuboDesAct);  

   printf("\t Contiene %d registros de los cuales se han desbordado %d:\n",regC.numReg,regC.numRegDes);
   	
   densidadOcupacion = 100*regC.numReg/((regC.nCubos+regC.nCubosDes)*C);
   printf("Densidad ACTUAL de ocupación: %d \n\t(MÍNIMA permitida %f  MÁXIMA permitida %f)\n",
   				densidadOcupacion,regC.densidadMin,regC.densidadMax);
   
   
   if (densidadOcupacion>regC.densidadMax) {
   	printf("No se respeta la densidad máxima de ocupacion\n");
   }	

   if (densidadOcupacion<regC.densidadMin) {
   	printf("No se respeta la densidad mínima de ocupacion\n");
   }	
return 0;	
}
//Funcion para la creacion de archivo vacio, proporcionada en dispersion.h
int creaHvacio(char *fichHash,regConfig *reg){
   int totC = reg->nCubos + reg->nCubosDes;int i=0;
   tipoCubo c;FILE *f;
   memset(&c,0,sizeof(c));
   f=fopen(fichHash,"wb");
   if (f==NULL)
   {
      return -2;
   }
   if(fwrite(reg,sizeof(regConfig),1,f)!=1)
   {
      fclose(f);
      return -5;
   }
   for ( i = 0; i < totC; i++)
   {
      if(fwrite(&c,sizeof(tipoCubo),1,f)!=1){
         fclose(f);
         return -5;
      }
   }
   fclose(f);
   return 0; 
}
//Crea el Hash
int creaHash(char *fichEntrada,char *fichHash, regConfig *regC){
   FILE *fIn,*fOut;
   tipoReg reg;
   int pos,i,dens;
   regC->numReg=0;
   regC->numRegDes=0;
   regC->nCuboDesAct=regC->nCubos;
   if (creaHvacio(fichHash,regC)<0)
   {
      return -2;
   }
   fIn = fopen(fichEntrada,"rb");
   fOut=fopen(fichHash,"r+b");
   if (fIn==NULL || fOut==NULL)
   {
      return -2;
   }
   while (fread(&reg,sizeof(tipoReg),1,fIn)==1)
   {
      pos = insertar(fOut,&reg, regC);
      if (pos==-1)
      {
         fclose(fIn);fclose(fOut);
         return -3;
      }
      regC->numReg++;
   }
   fseek(fOut,0,SEEK_SET);
   fwrite(regC,sizeof(regConfig),1,fOut);
   fclose(fIn);fclose(fOut);
   dens = 100 * regC->numReg / ((regC->nCubos+regC->nCubosDes)*C);
   if(dens>regC->densidadMax)return -3;
   if(dens<regC->densidadMin)return -4;
   return regC->numRegDes;
}
int busquedaHash(FILE *fHash, tipoReg *reg, tPosicion *posicion){
   regConfig regC;
   tipoCubo c;
   int i,numC,cubDes;
   fseek(fHash,0,SEEK_SET);
   if(fread(&regC,sizeof(regConfig),1,fHash)!=1){
      return -1;
   }
   numC=funcionHash(reg,regC.nCubos);
   fseek(fHash,sizeof(regConfig)+numC*sizeof(tipoCubo),SEEK_SET);
   if (fread(&c,sizeof(tipoCubo),1,fHash)!=1)
   {
      return -1;
   }
   
   //Recorrido de Registros
   for (i = 0; i < c.numRegAsignados && i<C; i++)
   {
      if (cmpClave(&c.reg[i],reg)==1)
      {
         posicion->cubo=numC;
         posicion->cuboDes =-1;
         posicion->posReg=i;
         return numC;
      }
   }
   if (c.desbordado)
   {
      for (int j = 0; j < regC.numRegDes; j++)
      {
         cubDes=regC.nCuboDesAct + (j/C);
         fseek(fHash,sizeof(regConfig)+cubDes * sizeof(tipoCubo),SEEK_SET);
         if (fread(&c,sizeof(tipoCubo),1,fHash)!=1)
         {
            return -1;
         }
         for ( i = 0; i < c.numRegAsignados && i<C; i++)
         {
            if (cmpClave(&c.reg[i],reg)==1)
            {
               posicion->cubo=numC;
               posicion->cuboDes =cubDes;
               posicion->cubo=i;
               return numC;
            }
         }
         
         
      }
      
   } 
   return -1;
}
int modificarReg(FILE *fHash, tipoReg *reg, tPosicion *posicion){
   tipoCubo cubo;
   long offset;
   int cuboEncontrado=busquedaHash(fHash,reg,posicion);
   if (cuboEncontrado == -1)
   {
      return -1;
   }
   offset = sizeof(regConfig) +posicion->cuboDes*sizeof(tipoCubo);
   if (posicion->cuboDes<0)
   {
      offset=sizeof(regConfig) +posicion->cubo*sizeof(tipoCubo);
   }
   fseek(fHash,offset,SEEK_SET);
   fread(&cubo,sizeof(tipoCubo),1,fHash);
   cubo.reg[posicion->posReg]=*reg;
   fseek(fHash,-sizeof(tipoCubo),SEEK_CUR);
   fwrite(&cubo,sizeof(tipoCubo),1,fHash);
   return 0;   
}
int insertar(FILE *f, tipoReg *reg, regConfig *regC){
   tipoCubo cubo;
   int cuboId=funcionHash(reg,regC->nCubos);
   fseek(f,sizeof(regConfig)+cuboId * sizeof(tipoCubo),SEEK_SET);
   fread(&cubo,sizeof(tipoCubo),1,f);
   cubo.numRegAsignados++;
   if (cubo.numRegAsignados<=C)
   {
      cubo.reg[cubo.numRegAsignados-1]=*reg;
      fseek(f,-sizeof(tipoCubo),SEEK_CUR);
      fwrite(&cubo,sizeof(tipoCubo),1,f);
      return cuboId;
   }
   cubo.desbordado=1;
   fseek(f,-sizeof(tipoCubo),SEEK_CUR);
   fwrite(&cubo,sizeof(tipoCubo),1,f);
   regC->numRegDes++;
   fseek(f,0,SEEK_SET);
   fwrite(regC,sizeof(regConfig),1,f);
   return desborde(f,reg,regC);  
}
int desborde(FILE *fHash,tipoReg *reg, regConfig *regC){
   tipoCubo cubo;
   int pos,idenxDesb=regC->numRegDes-1,cuboDes;
   cuboDes=regC->nCuboDesAct + (idenxDesb/C);
   if (cuboDes>=regC->nCuboDesAct+regC->nCubosDes)
   {
      return -1;
   }
   fseek(fHash,sizeof(regConfig)+cuboDes*sizeof(tipoCubo),SEEK_SET);
   fread(&cubo,sizeof(tipoCubo),1,fHash);
   pos =cubo.numRegAsignados++;
   cubo.reg[pos]=*reg;
   cubo.desbordado=1;
   fseek(fHash,-sizeof(tipoCubo),SEEK_CUR);
   fwrite(&cubo,sizeof(tipoCubo),1,fHash);
   return cuboDes;
}
int buscarReg(FILE *f,tipoReg *reg,void *dni){
   tPosicion pos;
   return busquedaHash(f,reg,&pos);

}
int insertarReg(FILE *f,tipoReg *reg){
   regConfig regC;
   int c;
   fseek(f,0,SEEK_SET);
   if ((fread(&regC,sizeof(regC),1,f))!=1)
   {
      return -1;
   }
   c=insertar(f,reg,&regC);
   fseek(f,0,SEEK_SET);
   fwrite(&regC,sizeof(regC),1,f);
   return c; 
}