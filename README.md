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
    
Por cada vertice j+1, recorremos todos sus vecinos k, en el caso de que el vecino k este coloreado con un color c, asignamos en la posicion c del arreglo con los colores disponibles para j un 1.

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

Ahora devolvemos como resultado de greedy el color mas alto con el cual hemos coloreado el grafo W.

```c
return highestcolor;
```

_Bipartito()_: Devuelve 1 si el grafo es Bipartito, 0 caso contrario.

¿Como saber si un grafo es bipartito?
>En teoría de grafos, un grafo bipartito es un grafo G=(N,E) cuyos vértices se pueden separar en dos conjuntos disjuntos U y V, es decir, tal que se cumple: U union V = N y U intercepcion V = VACIO de manera que las aristas sólo pueden conectar vértices de un conjunto con vértices del otro; es decir: no existe ninguna arista E(u1,u2) ni E(v1,v2).

Apliquemos la tecnica de dividir el grafo en dos conjuntos disjuntos. Empezamos coloreando el primer vertice j con el color 1.

```c
(W->listV[(W->orden[0])])->color = 1; 
```

Luego descoloreamos todos los demas vertices. 

```c
for (i = 1; i < W->v; i++) {
   (W->listV[(W->orden[i])])->color = -1;                               //Coloreo el resto de los vertices con -1
   }
```

Ahora creamos un arreglo con los colores disponibles para colorear el grafo (Como quiero saber si es bipartito necesito solo 2 colores)

```c
int coloresdisponibles[1];                                               //Creo un arreglo de dos colores
for (x = 0; x < 2; x++) {
    coloresdisponibles[x] = 0;                                           //Le asigno 0 a los dos valores del arreglo
}
```

Ahora para cada vertice j+1, recorremos sus vecinos k y nos fijamos si k esta descoloreado esto quiere decir que podemos pintar el j tanto con el color 1 como con el color 2, si k esta coloreado con 1 solo podremos pintar j con 2 y si k esta coloreado con 2 solo podremos colorear j con 1. Pero que pasa si un vecino k de j esta coloreado con 1 y otro vecino k de j esta coloreado con 2, en este caso necesitariamos un 3 color para poder colorear este vertice j, por lo tanto no seria un grafo bipartito.

```c
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

```

En caso de que las iteraciones llegen al final esto quiere decir que ele grafo fue coloreado con dos colores por lo tanto podemos devolver el valor numerico 1 para indicar que el grafo s bipartito.


```c
return 1;
```

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

## 8. Dificultades ##

Por una cuestion de tiempo y como fuimos siguiendo el PDF del Proyecto en orden las funcion AleatorizarVertices() y ReordenManteniendoBloqueColores(), no estan testeadas ni bien implementadas creemos.

El proyecto nos parecio entretenido, tiene al principio una cuota de dificultad extra cuando no se tiene una estructura lo suficientemente solida como para resolver las inquietudes que van surgiendo, pero una vez sorteada esta dificultad el proyecto se hace mucho mas sencillo y llevadero.
