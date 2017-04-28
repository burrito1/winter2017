#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned int u32;
typedef struct Grafo *WinterIsHere;
typedef struct Vertice *VertexIsHere;


WinterIsHere NewWinter();
int LoadWinter(WinterIsHere W);
WinterIsHere WinterIsComing();
int Primavera(WinterIsHere W);


u32 NombreDelVertice (WinterIsHere W, u32 x);
u32 ColorDelVertice (WinterIsHere W, u32 x);
u32 GradoDelVertice (WinterIsHere W, u32 x);
u32 IesimoVecino (WinterIsHere W, u32 x, u32 i);
