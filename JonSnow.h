#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef unsigned int u32;
typedef struct Grafo *WinterIsHere;
typedef struct Vertice *VertexIsHere;

//3. Creacion y Destruccion del Grafo
WinterIsHere NewWinter();
int LoadWinter(WinterIsHere W);
WinterIsHere WinterIsComing();
int Primavera(WinterIsHere W);

//4. Coloreo
u32 Greedy(WinterIsHere W);
int Bipartito (WinterIsHere W);

//7. Funciones de los vertices
u32 NombreDelVertice (WinterIsHere W, u32 x);
u32 ColorDelVertice (WinterIsHere W, u32 x);
u32 GradoDelVertice (WinterIsHere W, u32 x);
u32 IesimoVecino (WinterIsHere W, u32 x, u32 i);

//5. Funciones info grafo
u32 NumeroDeVertices(WinterIsHere W);
u32 NumeroDeLados(WinterIsHere W);
u32 NumeroDeVerticesDeColor(WinterIsHere W, u32 i);
u32 NumeroDeColores(WinterIsHere W);
u32 IesimoVerticeEnElOrden(WinterIsHere W, u32 i);

//6. Reordenamientos
void OrdenNatural(WinterIsHere W);
void OrdenWelshPowell(WinterIsHere W);
void AleatorizarVertices(WinterIsHere W, u32 x);
void ReordenamientoManteniendoBloqueColores(WinterIsHere W, u32 x);

/*
Gonzalo Nicolas Rivero ----- gon.rivero10@gmail.com
Jenaro Calvineo ------------ jen.calvineo@live.com.ar
*/


