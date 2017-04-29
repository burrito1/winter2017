#include "JonSnow.h"
#include <stdlib.h>
#include <stdio.h>

//#define FILENAME      "xg22"          //Usado para implementar test y no tener que cargar el FILENAME 1000 veces
#define mode            "r"             //Modo en el que se lee el archivo input

int global = 0;                         //Variable global de AddVertex

typedef struct Grafo {
    VertexIsHere *listV;                //Lista de todos vertices
    u32 v;                              //Cantidad vertices
    u32 w;                              //Cantidad de lados
    u32 *orden;                         //Orden de indices para greedy
} WinterSt;

typedef struct Vertice {
    u32 name;                           //Nombre del vertice
    u32 color;                          //Color asignado al vertice
    u32 grade;                          //Cantidad de vecinos del vertice
    u32 *ngbrs;                         //Arreglo con indices a sus vecinos
} VerticeSt;


WinterIsHere NewWinter() {
    WinterIsHere W = calloc(1, sizeof(struct Grafo));
    if(W != NULL){
        W->v = 0;
        W->w = 0;
    }

    return W;
}

u32 AddVertex(WinterIsHere W, unsigned int x){
    u32 i = 0;
    while(i<global && x != W->listV[i]->name){                   //Busco la posicion del vertice i etiquetado
        i++;
    }
    if(i==global){                                              //Si la posicion es igual a global no esta en la lista
        
        W->listV[i] = calloc(1, sizeof(VertexIsHere));          //Reservo espacio
        W->orden[i] = i;                                        //Agrego su indice al orden para Greedy
        W->listV[i]->name = x;                                  //Lo etiqueto x (el parametro)
        W->listV[i]->color = i+1;                               //Le doy color igual a su indice+1 asi tiene un coloreo propio el grafo
        W->listV[i]->grade++;                                   //Aumento su grado a 1
        global++;                                               //Aumento global porque la lista crecio
        
        //printf("NEW V: %u:(%u, %u, %u, [])\n", x, W->listV[i]->name, W->listV[i]->color,W->listV[i]->grade);
        
        return i;
    } else {                                                    //Esto quiere decir que ya estaba en la lista
        
        W->listV[i]->grade++;                                   //Aumento su grado porque algun vecino de el llamo a AddVertex()
        
        //printf("GRADE ++ IN V: %u:(%u, %u, %u, [])\n", x, W->listV[i]->name, W->listV[i]->color,W->listV[i]->grade);
        return i;
    }
}

void AddNeighbors(WinterIsHere W, u32 i, u32 ngbr){
    u32 j = 0;
    while(W->listV[i]->ngbrs[j] != 0) j++;
    W->listV[i]->ngbrs[j] = ngbr;      						     //Agrego el vecino en la posicion j de vecinos del vertice i
}


int LoadWinter(WinterIsHere W){
    
    FILE *ifp;
    char FILENAME[80];
    printf("Ingrese el nombre del archivo\n");
	scanf("%s", FILENAME);
    ifp = fopen(FILENAME, mode);
    char c;

    if (ifp == NULL) {
        printf("No se puede abrir el archivo\n");
        exit(1);
    }

    printf ("Reading FILE: %s\n", FILENAME);
    while(fscanf(ifp, "%c", &c) != EOF && c != 'p')
        while(fscanf(ifp, "%c", &c) != EOF && c != '\n');
    
    fscanf(ifp, "%*s %d %d\n", &W->v, &W->w);

    W->listV = calloc(W->v, sizeof(VertexIsHere));
    W->orden = calloc(W->v, sizeof(u32));
    
    u32 i = 0;
    u32 x1;
    u32 x2;
    u32 Verticei;
    u32 Verticej;
    u32 xi1[W->w];
    u32 xj2[W->w];

    while(fscanf(ifp, "e %u %u\n", &x1, &x2) != EOF)
    {   
        Verticei=AddVertex(W,x1);                                      //AddVertex del input en la posicion x1
        Verticej=AddVertex(W,x2);                                      //AddVertex del input en la posicion x2
        xi1[i] = Verticei;
        xj2[i] = Verticej;
        i++;
    }
    
    for(i=0; i<W->v;i++){
        W->listV[i]->ngbrs = calloc(W->listV[i]->grade, sizeof(u32));  //Espacio en el arreglo de vecinos dependiendo del grado que tenga i
    }

    for(i=0; i<W->w;i++){
        AddNeighbors(W,xi1[i],xj2[i]);                                 //Agrego el vecino x2 del vertice x1
        AddNeighbors(W,xj2[i],xi1[i]);                                 //Agrego el vecino x1 del vertice x2
    }

    return 1;
}

WinterIsHere WinterIsComing(){

	printf("Winter is comming\n");
    WinterIsHere W = NewWinter();
    int error;
    error = LoadWinter(W);

    if (error != 1){
    	return NULL;                                                   //Devuelve un puntero a NULL en caso de error
    }
    else{
    	return W;
    }
    
}

int Primavera(WinterIsHere W){
    
    int i = 0;
    for(i=0; i<W->v;i++){
        free(W->listV[i]->ngbrs);                                      //Primero libero los vecinos de i
        free(W->listV[i]);                                             //Segundo libero el vertice i
    }
    free(W->orden);                                                    //Libero el arreglo de indices
    free(W);
    W = NULL;
    return 1;
}

u32 Greedy(WinterIsHere W){
	
	/*
	Fuente: http://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/

	1. Color first vertex with first color.
	2. Do following for remaining V-1 vertices.
          a) Consider the currently picked vertex and color it with the 
             lowest numbered color that has not been used on any previously
             colored vertices adjacent to it. If all previously used colors 
             appear on vertices adjacent to v, assign a new color to it.

	*/

	u32 i,j,k;
    u32 x;
    u32 highestcolor = 0;                                                  //Color 0 en caso de recibir un grafo NULL

    (W->listV[(W->orden[0])])->color = 1;                                  //Le asigno color 1 al primer vertice

    for (i = 1; i < W->v; i++) {
        (W->listV[(W->orden[i])])->color = -1;                             //Le asigno color -1 al resto de los vertices
    }
    
    int coloresdisponibles[W->v];                                          //Creo un arrlego entero de W->v valores
    for (x = 0; x < W->v; x++) {
        coloresdisponibles[x] = 0;                                         //Le asigno 0 a cada valor del arreglo
    }

    u32 index;
    for (j = 1; j < W->v; j++) {                                           //Recorro j
        
        for (k = 0; k < (W->listV[(W->orden[j])])->grade; k++) {           //Recorro k vecinos de j
            index = W->listV[(W->orden[j])]->ngbrs[k];
            if (W->listV[index]->color != -1) {                            //Si el color en el k vecino de j no es -1 (Ya esta pintado)
                coloresdisponibles[(W->listV[index])->color] = 1;          //Marco en mi arreglo de colores como 1 en la posicion color de k
            }                                                              //De esta forma sabemos que el color igual al indice de esa posicion
        }                                                                  //No puede ser usado para pintar j

        for (x = 1; x < W->v; x++) {
            if (coloresdisponibles[x] == 0) {                              //Recorro el arreglo hasta encontrar un color disponible
                break;
            }
        }

        (W->listV[(W->orden[j])])->color = x;                              //Pinto j con el color x donde x es la posicion+1 del primer disponible
        if(x > highestcolor){
            highestcolor = x;                                              //Si el nuevo color es mas grande que mi mayor color anterior lo cambio
        }

        for (k = 0; k < (W->listV[(W->orden[j])])->grade; k++) {
            index = W->listV[(W->orden[j])]->ngbrs[k];
            if (W->listV[index]->color != -1) {
                coloresdisponibles[(W->listV[index])->color] = 0;          //Ajusto mi arreglo de colores para mi proximo j
            }
        }
    }

    return highestcolor;
}

int Bipartito (WinterIsHere W){

	u32 i,j,k;
    u32 x;

	(W->listV[(W->orden[0])])->color = 1;                                    //Coloreo el primer vertice con 1

    for (i = 1; i < W->v; i++) {
        (W->listV[(W->orden[i])])->color = -1;                               //Coloreo el resto de los vertices con -1
    }

    int coloresdisponibles[1];                                               //Creo un arreglo de dos colores
    for (x = 0; x < 2; x++) {
        coloresdisponibles[x] = 0;                                           //Le asigno 0 a los dos valores del arreglo
    }
	
	u32 index;
    for (j = 1; j < W->v; j++) {                                             //Recorro cada j
        
        for (k = 0; k < (W->listV[(W->orden[j])])->grade; k++) {             //Recorro cada vecino de k de j
            index = W->listV[(W->orden[j])]->ngbrs[k];
            if (W->listV[index]->color == -1) {                              //Si el color del vecino k de j es -1 (No esta pintado)
                coloresdisponibles[0] = 0;                                   //->  Puedo pintarlo como 1
                coloresdisponibles[1] = 0;                                   //->  Puedo pintarlo como 2
            }else if (W->listV[index]->color == 1) {                         //Si el color del vecino k de j es 1 (Pintado con Azul)
            	coloresdisponibles[0] = 1;                                   //->  No puedo pintarlo como 1
            	coloresdisponibles[1] = 0;                                   //->  Si puedo pintarlo como 2
            }else if (W->listV[index]->color == 2) {                         //Si el color del vecino k de j es 2 (Pintado con Negro)
            	coloresdisponibles[0] = 0;                                   //->  Si puedo pintarlo como 1
            	coloresdisponibles[1] = 1;                                   //->  No puedo pintarlo como 2
            }
        }

        if (coloresdisponibles[0] == 0 && coloresdisponibles[1] == 1) {
          	W->listV[(W->orden[j])]->color = 1;                             //Pinto j como 1
        } else if (coloresdisponibles[0] == 1 && coloresdisponibles[1] == 0){
          	W->listV[(W->orden[j])]->color = 2;                             //Pinto j como 2  
        } else {
          	return 0;                                                       //Como el arreglo de colores es [1,1] no tengo colores que 
        }                                                                   //asignarle a j, por lo tanto devuelvo 0 (No es bipartito)
            

        coloresdisponibles[0] = 0;                                          //Ajusto los colores diponibles para el proximo j
        coloresdisponibles[1] = 0;
        
    }

    return 1;
}

// FUNCIONES DEL VERTICE

u32 NombreDelVertice (WinterIsHere W, u32 x){

	u32 r;
	r = W->listV[x]->name;

	return r;
}

u32 ColorDelVertice (WinterIsHere W, u32 x){

	u32 r;
	r = W->listV[x]->color;

	return r;
}

u32 GradoDelVertice (WinterIsHere W, u32 x){

	u32 r;
	r = W->listV[x]->grade;

	return r;
}

u32 IesimoVecino (WinterIsHere W, u32 x, u32 i){

	u32 r, k;
	k = W->listV[(W->orden[x])]->ngbrs[i];
	r = W->listV[k]->name;

	return r;
}

u32 NumeroDeVertices(WinterIsHere W){

	u32 r;
	r = W->v;

	return r;
}

u32 NumeroDeLados(WinterIsHere W){

	u32 r;
	r = W->w;
	
	return r;
}

u32 NumeroDeVerticesDeColor(WinterIsHere W, u32 i){

	u32 r = 0;
	u32 j = 0;
	for (j=0; j< W->v; j++){
		if ((W->listV[j]->color) == i){
			r++;
		}
	}
	
	return r;
}

u32 NumeroDeColores(WinterIsHere W){

	u32 j = 0;
	u32 c = 1;
	for (j=0; j< W->v; j++){
		if ((W->listV[j]->color) > c){
			c = W->listV[j]->color;
		}
	}

	return c;
}

u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i){

	u32 r;
	r = W->listV[(W->orden[i])]->name;

	return r;
}

//REORDENAMIENTO

int natcomp (const void * a, const void * b){
	return ( *(int*)a - *(int*)b );
}

int wpcomp (const void * a, const void * b){

    struct Vertice x1 = *(const struct Vertice *)a;
    struct Vertice x2 = *(const struct Vertice *)b;
    if (x1.grade < x2.grade)
	    return 1; 
    else if (x1.grade > x2.grade)
	    return -1;   
    else
	    return 0;
}

int bloque0comp (const void * a, const void * b){

	return 1

}

int bloque1comp (const void * a, const void * b){

    struct Vertice x1 = *(const struct Vertice *)a;
    struct Vertice x2 = *(const struct Vertice *)b;
    if (x1.color > x2.color)
        return 1; 
    else if (x1.color < x2.color)
        return -1;   
    else
	    return 0;
}

int bloque2comp (const void * a, const void * b){

	return 1;

}

int bloque3comp (const void * a, const void * b){

	return 1;
}

int bloque4comp (const void * a, const void * b){

	return 1;
}


void OrdenNatural(WinterIsHere W){

	qsort(W->orden, W->v, sizeof(u32), natcomp);
}

void OrdenWelshPowell(WinterIsHere W){

	qsort(W->orden, W->v, sizeof(VertexIsHere), wpcomp);
}

void ReordenamientoManteniendoBloqueColores(WinterIsHere W, u32 x){

	if(x==0){
	    qsort((W->orden),(W->v),sizeof(VertexIsHere), bloque0comp);
	}
	else if(x==1){
		    qsort((W->orden),(W->v),sizeof(VertexIsHere), bloque1comp);
	}
	else if(x==2){
	    qsort((W->orden),(W->v),sizeof(VertexIsHere), bloque2comp);
	}
	else if(x==3)
	    qsort((W->orden),(W->v),sizeof(VertexIsHere), bloque3comp);
	else{
	    qsort((W->orden),(W->v),sizeof(VertexIsHere), bloque4comp);
	}
}


int main(void) {

	WinterIsHere W = WinterIsComing();

    int i;
    u32 sumofgrades = 0;
    u32 greedyresult = 0;
    int bip = 0;
    
    greedyresult = Greedy(W);

   	bip = Bipartito(W);

    for(i=0;i<W->v;i++){
    	//printf("VERTEX %d of %u: (%u, %u, %u, [x])\n", i+1, W->v, W->listV[i]->name, W->listV[i]->color,W->listV[i]->grade);
    	sumofgrades = sumofgrades + W->listV[i]->grade;
    }
    
    u32 vertices, lados, maxcolor;

    vertices = NumeroDeVertices(W);
    lados = NumeroDeLados(W);
    maxcolor = NumeroDeColores(W);

    printf ("...............................\n");
    printf ("Grafo W:\n");
    printf ("-> Vertices: %u\n", vertices);
    printf ("-> Lados: %u\n", lados);
    printf ("-> Suma de Grados: %u\n", sumofgrades);
    printf ("-> Cantidad de colores: %u\n", maxcolor);
    printf ("-> W tiene un coloreo propio\n");
   	printf ("->El resultado de Greedy es: %u\n", greedyresult);
   	printf ("->El resultado de Bipartito es: %d\n", bip);


    return 1;
}