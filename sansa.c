#include "sansa.h"
#include <stdlib.h>
#include <stdio.h>

#define FILENAME        "xg25"
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
        //printf("GRADE ++ IN V: %u:(%u, %u, %u, [])\n", x, W->listV[i]->name, W->listV[i]->color,W->listV[i]->grade);
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
        Verticei=AddVertex(W,x1);
        Verticej=AddVertex(W,x2);
        xi1[i] = Verticei;
        xj2[i] = Verticej;
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
    int i = 0;
    for(i=0; i<W->v;i++){
        free(W->listV[i]->ngbrs);
        free(W->listV[i]);
    }
    free(W->orden);
    free(W);
    W = NULL;
    return 1;
}

u32 Greedy(WinterIsHere W){
	

	u32 i,j,k;
    u32 x;
    u32 highestcolor = 0;

    (W->listV[(W->orden[0])])->color = 1;

    for (i = 1; i < W->v; i++) {
        (W->listV[(W->orden[i])])->color = -1;
    }
    
    int coloresdisponibles[W->v];
    for (x = 0; x < W->v; x++) {
        coloresdisponibles[x] = 0;
    }
    u32 index;
    for (j = 1; j < W->v; j++) {
        
        for (k = 0; k < (W->listV[(W->orden[j])])->grade; k++) { 
            index = W->listV[(W->orden[j])]->ngbrs[k];
            if (W->listV[index]->color != -1) {
                coloresdisponibles[(W->listV[index])->color] = 1; 
            }
        }

        for (x = 1; x < W->v; x++) {
            if (coloresdisponibles[x] == 0) {
                break;
            }
        }

        (W->listV[(W->orden[j])])->color = x;
        if(x > highestcolor){
            highestcolor = x;
        }

        for (k = 0; k < (W->listV[(W->orden[j])])->grade; k++) {
            index = W->listV[(W->orden[j])]->ngbrs[k];
            if (W->listV[index]->color != -1) {
                coloresdisponibles[(W->listV[index])->color] = 0; 
            }
        }
    }

    return highestcolor;
}


int main(void) {

	WinterIsHere W = WinterIsComing();

    int i;
    u32 sumofgrades = 0;
    u32 greedyresult = 0;

    
    greedyresult = Greedy(W);

    for(i=0;i<W->v;i++){
    	//printf("Vector %d of %u: (%u, %u, %u, [x])\n", i+1, W->v, W->listV[i]->name, W->listV[i]->color,W->listV[i]->grade);
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

   	
   	/*
   	int j;
   	for(j=0;j<W->v;j++){
    	printf("Vector %d of %u: (%u, %u, %u, [x])\n", j+1, W->v, W->listV[j]->name, W->listV[j]->color,W->listV[j]->grade);
    }
    */
   	printf ("El resultado de Greedy es: %u\n", greedyresult);

    return 1;
}