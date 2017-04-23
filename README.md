# winter2017

## Proyecto de md2 ##

Comandos consola para ejecutar en linux

gcc -Wall -Werror -o exe sansa.c

./exe


#### sansa.c ####

Estructuras utilizada:

    typedef struct Grafo {
        VectorIsHere *listV;        //Lista de vertices
        u32 v;                      //Cantidad vertices
        u32 w;                      //Cantidad de lados
        u32 *orden;                 //Orden de indices para greedy
    } WinterSt;

Donde listV es un arreglo con todos los vertices:

    typedef struct Vertice {
        u32 name;                   //Nombre del vertice
        u32 color;                  //Color asignado al vertice
        u32 grade;                  //Cantidad de vecinos del vertice
        u32 *ngbrs;                 //Arreglo con indices a sus vecinos
    } VerticeSt;




