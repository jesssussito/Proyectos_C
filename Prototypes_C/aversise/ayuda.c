//obtenerVsinGent
int i;
for ( i = 0; i <G->orden; i++)
{
    if (G->directorio[i].gradoEntrada == 0 && G->directorio[i].ordenTopo ==-1)
    {
        return i;
    }
    
}
return -1;
//orden topo normal
int vAct,i;
tipoArco *aux;
for ( i = 0; i <G->orden; i++)
{
    vAct = obtenerVsinGent(G);
    if (vAct ==-1)
    {
        /* code */
    }
    G->directorio[vAct].ordenTopo =i;
    aux=G->directorio[i].ListaAdyacencia;
    while(aux!=NULL){
        G->directorio[vAct].gradoentrada--;
        aux=aux->sig;
    }
}
//OrdentopoCola
Cola c;
int i,vAct;
tipoArco *aux;
for ( i = 0; i < G->orden; i++)
{
    if (G->directorio[i].gradoEnt==0)
    {
        insertarCola(i);
    }
    
}
i=1;
while(!vacia(c)){
    vAct=sacarCola(c);
    G->direcorio[vAct].ordenTopo=i;
    i++;
    aux=G->directorio[vAct].ListaAdyacencia;
    while(aux!=NULL){
        G->directorio[vAct].gradoEnt--;
        if (G->directorio[vAct].gradoEnt==0)
        {
            insertarCola(aux->idv);
        }
        aux=aux->sig;
    }
}
if (i>=G->orden-1)
{
    /* code */
}
///obtenerVminNoAlcanzado
int i,vMin=-1;
for ( i = 0; i < G->orden; i++)
{
    if (G->directorio[i].alcanzado==0 && (vMin == -1 || G->directorio[i].dist < G->directorio[vMin].dist))
    {
        vMin=i;
    }
    
}
return vMin;
//Dijkstra
int vAct,i,distNueva;
tipoArco *aux;
iniciar(G);
G->directorio[vIni].ant=-1;
G->directorio[vIni].dist=0;
for ( i = 0; i < G->orden; i++)
{
    vAct=obtenerVminNoAlcanzado(G);
    if (vAct == -1)
    {
        /* code */
    }
    
    G->directorio[vAct].alcanzado=1;
    aux=G->directorio[vAct].ListaAdyacencia;
    while(aux!=NULL){
        distNueva = G->directorio[vAct].dist + aux->peso;
        if (distNueva < G->directorio[aux->idV].dist)
        {
            G->directorio[aux->idV].ant=vAct;
            G->directorio[aux->idV].dist = distNueva;
        }
        aux=aux->sig;
    }
}
typedef struct n{
    int idV,peso;
}tipoElemento;
//DijkstraMont
Monticulo M;
tipoElemento elem;
tipoArco *aux;
int distN;
inicar(G);
inicarMont(&M);
G->directorio[vIni].ant=-1;
G->directorio[vIni].dist=0;
elem.idV=vIni;
elem.peso=0;
insertar(&M,elem);
while(!vacio(&M)){
    elem=eliminarMIn(&M);
    if (G->directorio[elem.idV].alcanzado==0)
    {
        G->directorio[elem.idV].alcanzado=1;
        aux=G->directorio[elem.idV].ListaAdyacencia;
        while (aux!=NULL)
        {
            distN = G->directorio[aux->idV].dist + aux->peso;
            if (distN <G->directorio[aux->idV].dist )
            {
                G->directorio[aux->idV].dist=distNueva;
                G->directorio[aux->idV].ant=elem.idV;
                elem.peso=distNueva;
                elem.idV=aux->idV;
                insertarMont(elem);
            }
            aux=aux->sig;
        }
        
    }
    
}
