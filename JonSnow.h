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

u32 NumeroDeVertices(WinterIsHere W);
u32 NumeroDeLados(WinterIsHere W);
u32 NumeroDeVerticesDeColor(WinterIsHere W, u32 i);
u32 NumeroDeColores(WinterIsHere W);
u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i);

