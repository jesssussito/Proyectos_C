#include "secuencial.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int leeSecuencial(char *fichero){
    tAlumno reg;
    int r=0;
    FILE *f = fopen(fichero,"rb");
    if (f==NULL)
    {
        return -1;
    }
    while (fread(&reg,sizeof(reg),1,f)==1)
    {
        printf("NRR %3d",r);
        mostrarReg(&reg);
        r++;
    }
    fclose(f);
    return r;
    
    
}
int buscaReg(FILE *fSecuencial, tAlumno *reg,char *dni){
    tAlumno tmp;
    int r=0;
    fseek(fSecuencial,0,SEEK_SET);
    while (fread(&tmp,sizeof(tmp),1,fSecuencial)==1)
    {
        if (strcmp(tmp.dni,dni)==0)
        {
            *reg=tmp;
            return r;
        }
        r++;
    }
    fclose(fSecuencial);
    return -1;
}
int insertaReg(char *fSecuencial, tAlumno *reg){
    long pos;
    int r=0;
    FILE *f=fopen(fSecuencial,"ab+");
    if (f==NULL)
    {
        return -1;
    }
    if (fwrite(reg,sizeof(*reg),1,f)!=1)
    {
        fclose(f);
        return -1;
    }
    pos=ftell(f);
    r=(int)(pos/sizeof(*reg))-1;
    fclose(f);
    return r;
}