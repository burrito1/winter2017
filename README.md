# Winter Graph Coloring 2017

## 1. Introducción ##

Integrantes:
* Gonzalo Nicolás Rivero
* Jenaro Calviño

Comandos consola para ejecutar en linux:

    gcc -Wall -Werror -o exe sansa.c

    ./exe


## 2. Estructura ##

Para el grafo se utilizo:

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


## 3. Construccion y destrucción del grafo ##

_NewWinter()_: Inicializa un grafo W.

_LoadWinter()_: Carga los valores obtenidos desde un archivo input a la estructura del grafo W.

_WinterIsComming()_: Devuelve el grafo W con un coloreo propio.

_Primavera()_: Libera memoria y destruye el grafo W.


## 4. Coloreo ##

_Greedy()_: Colorea el grafo W de la siguiente forma:

    1. Colorea el primer vertice con el primer color.
    2. Para los siguientes V-1 vertices:
        -> Colorear el vertice elejido con el menor color posible talque ninguno de sus vecinos tengan ese color
        -> En el caso de no ser posible y que todos los colores usados esten coloreando vecinos de v, pintar v con un nuevo color
        
_Bipartito()_: Devuelve 1 si el grafo es Bipartito, 0 caso contrario.


## 5. Informacion del Vertice ##

_NumeroDeVertices()_: Devuelve el numero de vertices de W.

_NumeroDeLados()_: Devuelve el numero de lados de W.

_NumeroVerticesDeColor()_: Devuelve el numero de vertices de color i.

_NumeroDeColores()_: La cantidad de colores utilizados en el coloreo de W en ese momento.

_IesimoVerticeEnElOrden()_: Devuelve la etiqueta del vertice i en el orden guardado en ese momento.

## 6. Funciones de ordenación ##

_OrdenNatural()_: Ordena los vertices en orden creciente de sus “nombres” reales.

_OrdenWelshPowell()_: Ordena los vertices de W de acuerdo con el orden Welsh-Powell, es decir, con los grados en orden
no creciente.

_AleatorizarVertices()_: Esta funcion ordena pseudoaleatoriamente los vertices de W, usando alguna funcion pseudoaleatoria que dependa deterministicamente de x. 

_ReordenManteniendoBloqueColores()_: Reordena el orden de los vertices manteniendo los bloques de vertices pintados por los mismos colores.


## 7. Funciones de los vertices ##

_NombreDelVertice()_: Devuelve el nombre real del vertice.

_ColorDelVertice()_: Devuelve el color con el que esta coloreado el vertice.

_GradoDelVertice()_: Devuelve el grado del vertice.

_IesimoVecino()_: Devuelve la etiqueta del vecino numero i del vertice.
