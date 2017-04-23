#include "sansa.h"
#include <stdlib.h>
#include <stdio.h>

#define FILENAME        "example.col"
#define mode            "r"
int global = 0;                 //Variable global de AddVertex

typedef struct Grafo {
    VectorIsHere *listV;        //Lista de vertices
    u32 v;                      //Cantidad vertices
    u32 w;                      //Cantidad de lados
    u32 *orden;                 //Orden de indices para greedy
} WinterSt;

typedef struct Vertice {
    u32 name;                   //Nombre del vertice
    u32 color;                  //Color asignado al vertice
    u32 grade;                  //Cantidad de vecinos del vertice
    u32 *ngbrs;                 //Arreglo con indices a sus vecinos
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
    while(i<global && x != W->listV[i]->name){
        i++;
    }
    if(i==global){
        W->listV[i] = calloc(1, sizeof(VectorIsHere));
        W->orden[i] = i;
        W->listV[i]->name = x;
        W->listV[i]->color = i+1;
        W->listV[i]->grade++;
        printf("NEW V: %u:(%u, %u, %u, [])\n", x, W->listV[i]->name, W->listV[i]->color,W->listV[i]->grade);
        global++;
        return i;
    } else {
        W->listV[i]->grade++;
        //printf("GRADE ++ in %u:(%u, %u, %u, [])\n", x, W->listV[i]->name, W->listV[i]->color,W->listV[i]->grade);
        return i;
    }
}

void AddNeighbors(WinterIsHere W, u32 i, u32 ngbr){
    u32 j = 0;
    while(W->listV[i]->ngbrs[j] != 0) j++;
    W->listV[i]->ngbrs[j] = ngbr;
}


int LoadWinter(WinterIsHere W){
    
    FILE *ifp;
    ifp = fopen(FILENAME, mode);
    char c;

    if (ifp == NULL) {
        printf("No se puede abrir el archivo\n");
        exit(1);
    }

    while(fscanf(ifp, "%c", &c) != EOF && c != 'p')
        while(fscanf(ifp, "%c", &c) != EOF && c != '\n');
    
    fscanf(ifp, "%*s %d %d\n", &W->v, &W->w);

    W->listV = calloc(W->v, sizeof(VectorIsHere));
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
        //printf("e: %u %u\n", x1, x2); //Esta linea permite ver que inputs esta leyendo del archivo en este momento
        Verticei=AddVertex(W,x1);
        Verticej=AddVertex(W,x2);
        xi1[i] = Verticei;
        xj2[i] = Verticej;
        //printf("(Verticei, Verticej) : (%u, %u)\n", Verticei, Verticej);
        //printf("(xi1[%u],xj2[%u]) : (%u, %u)\n", i, i, xi1[i], xj2[i]);
        i++;
    }
    
    printf("Agregando vecinos\n");
    printf ("...............................\n");

    for(i=0; i<W->v;i++){
        W->listV[i]->ngbrs = calloc(W->listV[i]->grade, sizeof(u32));
    }

    for(i=0; i<W->w;i++){
        AddNeighbors(W,xi1[i],xj2[i]);
        AddNeighbors(W,xj2[i],xi1[i]);
    }

    return 1;
}

WinterIsHere WinterIsComing(){

	printf("Winter is comming\n");
    WinterIsHere W = NewWinter();
    printf ("Reading FILE: %s\n", FILENAME);
    int error;
    error = LoadWinter(W);

    if (error != 1){
    	return NULL;
    }
    else{
    	return W;
    }
    
}

int Primavera(WinterIsHere W){
    //Destrye W y libera la memoria alocada. Return 1 = OK , 0 = ERROR
    return 1;
}

u32 Greedy(WinterIsHere W){

	int i, j, k, aux= 0;
	int c = 1;
	u32 highestcolor = 2;

	(W->listV[(W->orden[0])])->color = 1;              //Color 1 al primero

	for (i = 1; i < W->v; i++) {
        (W->listV[(W->orden[i])])->color = 2;          // A todos los coloremamos con 2
    }
    
    for (j = 1; j < W->v; j++) {
    	for (k = 0; k < (W->listV[(W->orden[j])])->grade; k++) {
    		aux = W->listV[(W->orden[j])]->ngbrs[k];
    		for (c = 1; c < highestcolor; c++) {
    			if (W->listV[(W->orden[j])]->color == W->listV[(W->orden[aux])]->color) {
   					highestcolor++;
   					printf("NEW COLOR: %u\n", highestcolor);
   					W->listV[(W->orden[aux])]->color = highestcolor;
   				}
			}
		}
	}

	return highestcolor;
}

int main(void) {

	WinterIsHere W = WinterIsComing();

    int i,j;
    u32 sumofgrades = 0;
    u32 greedyresult = 0;

    for(i=0;i<W->v;i++){
    	printf("Vector %d of %u: (%u, %u, %u, [x])\n", i+1, W->v, W->listV[i]->name, W->listV[i]->color,W->listV[i]->grade);
    	sumofgrades = sumofgrades + W->listV[i]->grade;
    }

    printf ("...............................\n");
    printf ("Grafo W:\n");
    printf ("-> Vertices: %u\n", W->v);
    printf ("-> Lados: %u\n", W->w);
    printf ("-> Suma de Grados: %u\n", sumofgrades);
    printf ("-> Cantidad de colores: %u\n", W->v);
    printf ("-> W tiene un coloreo propio\n");
    printf ("...............................\n");
   	printf ("Starting Greedy\n");

   	greedyresult = Greedy(W);

   	/*printf ("Increible el numero magico es: %u\n", greedyresult);
   	for(j=0;j<W->v;j++){
    	printf("Vector %d of %u: (%u, %u, %u, [x])\n", j+1, W->v, W->listV[j]->name, W->listV[j]->color,W->listV[j]->grade);
    }*/
   	printf ("Done :D\n");

    return 1;
}