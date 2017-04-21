# winter2017

## Proyecto de md2 ##

Comandos consola para ejecutar en linux

gcc -Wall -Werror -o exe sansa.c 
./exe


### Tipos de datos ###

u32:
Se utilizara el tipo de dato u32 para especificar un entero de 32 bits sin signo. Todos los enteros sin signo de 32 bits que
aparezcan en la implementacion deberan usar este tipo de dato.
Los grafos a colorear tendran una lista de lados cuyos vertices seran todos u32.

WinterSt:
Es una estructura, la cual debe contener toda la informacion sobre el grafo necesaria para correr su implementacion. La
definicion interna de la esta estructura es a eleccion de ustedes y debera soportar los metodos que se describiran mas adelante,
mas los metodos que ustedes consideren necesarios para implementar los algoritmos que esten implementando. Entre los
parametros debe haber como mınimo los necesarios para guardar los datos de un grafo (vertices y lados) pero ademas los
necesarios para guardar el coloreo que se tiene hasta ese momento en el grafo y cualquier informacion requerida en los
algoritmos a implementar.
IMPORTANTE: Como Greedy usa un orden de los vertices, en esta estructura tiene que estar guardado algun orden de
los vertices, y como vamos a cambiar ese orden repetidamente, debe ser algo que pueda ser cambiado.
Basicamente, debe tener lo que uds. consideren necesario para poder implementar las funciones descriptas abajo, de la
forma que a uds. les parezca mas conveniente.
El coloreo siempre debe cumplir que si es un coloreo con j colores entonces los colores son 1, 2, ..., j.

Estructura utilizada:

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


WinterIsHere:
es un puntero a una estructura de datos WinterSt
