#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned int u32;
typedef struct Grafo *WinterIsHere;
typedef struct Vertice *VectorIsHere;


WinterIsHere NewWinter();
int LoadWinter(WinterIsHere W);
WinterIsHere WinterIsComing();
int Primavera(WinterIsHere W);
