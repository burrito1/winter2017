# Winter Graph Coloring 2017

## 1. Introducción ##

Integrantes:
* Gonzalo Nicolás Rivero
* Jenaro Calviño

Recomendaciones:
* Leer el README.md desde https://github.com/burrito1/winter2017
* Leer el articulo/post de http://www.geeksforgeeks.org/graph-coloring-set-2-greedy-algorithm/

Comandos consola para compilar y ejecutar en linux:

    gcc -Wall -Werror -o exe sansa.c
    ./exe


## 2. Estructura ##

Para el grafo se utilizo:

    typedef struct Grafo {
        VertexIsHere *listV;        //Lista de vertices
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

¿Que hace greedy?
>1. Colorea el primer vertice con el primer color.
>2. Para los siguientes V-1 vertices: Colorear el vertice elejido con el menor color posible talque ninguno de sus vecinos tengan ese color. En el caso de no ser posible y que todos los colores usados esten coloreando vecinos de v, pintar v con un nuevo color c.

Coloreamos el primer vertice en el orden con el primer color.
    
```c
(W->listV[(W->orden[0])])->color = 1;
```
    
Descoloreamos todos los demas vertices.

```c
for (i = 1; i < W->v; i++) {
    (W->listV[(W->orden[i])])->color = -1;
}
```

Creamos un arreglo con todos los colores posibles con los que podemos coloriar a cada vertices, si el arreglo en la posicion x tiene un 0, significa que x+1 es un color disponible para pintar al vertice.

```c
int coloresdisponibles[W->v];
for (x = 0; x < W->v; x++) {
    coloresdisponibles[x] = 0;
}
```
    
Por cada vertice j, recorremos todos sus vecinos k, en el caso de que el vecino k este coloreado con un color c, asignamos en la posicion c del arreglo con los colores disponibles para j un 1.

```c
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

    W->listV[(W->orden[j])]->color = x;                              //Pinto j con el color x donde x es la posicion+1 del primer disponible
    
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
```    

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
