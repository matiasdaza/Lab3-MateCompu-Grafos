/*************************************************************/
/************************laboratorio 2************************/
/*
//Alumnos: Sergio Gonzalez, Cristobal Olivares.
//Profesor: Nicolas Thériault.
//Asignatura: Matemática Computacional.
//Fecha de entrega: 4 de Enero del 2015.
/*
/*************************************************************/
/************************Instrucciones************************/
/*
/*Para poder compilar: abra la terminal, ubiquese en el directorio.
donde se encuentre el codigo e ingrese el comando "gcc 'nombre_archivo' -o 'archivo_ejecucion'.
Para poder ejecutar: Ingrese el comando "./archivo_ejecucion.*/

//************************************************************/
//************************Librerias***************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Se define la estructura para trabajar 'pila' que nos facilitará trabajar con las dos pilas escenciales del programa, 'path' y 'ciclo'.
typedef struct pila
{
    int dest;
    struct pila *sig;
}
pila;

//Función pop para retirar el último elemento ingresado por 'push'
pila* pop(pila *lista)
{
    pila *t;
    t = lista;
    lista = lista->sig;
    free(t);
    return lista;
}

//Función en donde se ingresan los objetos a la pila
pila* push(pila *lista, int n)
{
    pila* t;
    t = calloc(n, sizeof(unsigned int*));
    t->sig = lista;
    t->dest = n;
    lista = t;
    return lista;
}

//Función que muestra los elementos d ela pila
void showeuler(pila *lista)
{
    pila* pasa = lista;
    if (pasa)
    {
    printf(" %d", pasa->dest);
    pasa = pasa->sig;
    }
    else
        return;
    while (pasa != 0)
    {
        printf("->%d", pasa->dest);
        pasa = pasa->sig;
    }
    printf("\n");
}

void print(unsigned int **p, int n);
unsigned int **genera_matriz(int n, float s);
void matriz_par(unsigned int **p, int n, float s);
pila* euler(int n, int unsigned **p);
int v_cercano(int n, int vertices[]);
int count_a(int vertice[], int n);

int main ()
{   
    int n, s;   //Se inicializa la Variable n, que almacenan tanto el largo como el ancho de la matriz.
    float probabilidad; //Se inicializa probabilidad, que almacena la probabilidad a utilizar y aleatorio, el numero al azar.
    printf("\nAl usar el metodo de la matriz de adyacencia, se asume que la matriz es de tipo n*n.\n");
    printf("\nIngrese el valor de n: ");    //Se pide ingresar el largo y ancho de la matriz.
    scanf("%d", &n);    //Lee el entero que se ingresa como largo y ancho.
    printf("\nIngrese el valor de la probabilidad que desea utilizar para el llenado de la matriz (0 < p < 1) >  : ");
    scanf("%f", &probabilidad); //Lee la variable probabilidad de tipo float.   
    s = probabilidad*100;   //Se multiplica el valor de la probabilidad ingresada por 100, para facil manipulacion.
    genera_matriz(n, s);    //Llamada a funcion que genera la matriz principal con largo-ancho y probabilidad de llenado como parametros.
    return 0; //Fin del programa.
 }


void print(unsigned int **p, int n) //Se toman como argumentos la matriz enviada, largo y ancho de la matriz.
{
    int i, j;   //Varibles de enteros que sirven como indices en los for.
    for (i = 0; i < n; i = i + 1)   //For que recorre el largo de la matriz.
    {                               //Se situa en la primera posicion del largo hasta llegar al final.
        {                           //Baja un espacio cuando 'i' aumenta.
            for (j = 0; j < n; j = j + 1)   //For que recorre ancho de la matriz. Adelanta un espacio cuando 'j' aumenta.
            printf("%d ", p[i][j]); //Instruccion que imprime los elementos de la matriz.
        }
    printf("\n");
    }
    printf("\n");
}

unsigned int **genera_matriz(int n, float s)    //Se toman como argumentos el largo y ancho de la matriz.           
{  
    srand(time(NULL));  //Semilla utilizada por la funcion rand() que genera numeros aleatorios.
    float aleatorio;    //Se inicializa la variable aleatorio, que almacena numeros al azar.                                              
    int i, j;   //Variables que sirven como indices en el for.
    unsigned int **p;   //Se crea el 'puntero de punteros' P, que servira como matriz.i
    p = calloc(n, sizeof(unsigned int*));                   
    for(i = 0; i < n; i = i + 1)    //For que recorre el largo del la fila.
        p[i] = calloc(n, sizeof(unsigned int)); //Por cada un espacio que se avanze en la fila, se agregan tantos espacios                                  como ancho haya ingresado el usuario.
    for(i = 0; i < n; i = i + 1)    //For que recorre fila de la matriz.    
    {
        for (j = 0 ; j < n; j = j + 1)  //For que recorre columna de la matriz.
        {       
            aleatorio = rand() % 101;   //Se almacenan en "aleatorio" numeros al azar de 0 hasta 100.
            if (s < aleatorio)  //Si la probabilidad es menor al numero aleatorio, se hace lo siguiente.
                p[i][j] = 1;    //Se situa en la posicion de la matriz segun el recorrido y agrega un 1.
            if (s > aleatorio)  //Si la probabilidad es mayor al numero aleatorio, se hace lo siguiente.
                p[i][j] = 0;    //Se situa en la posicion de la matriz segun el recorrido y agrega un 0.
            if (i == j) //Condicion que no permite vertices con lazos.
                p[i][j] = 0;    //Se agrega un 0 a la posicion.
        }
    }
    printf("\nLa matriz generada aleatoreamente es: \n\n"); //Se muestra por consola el mensaje.
    print(p, n);    //Se mandan como argumentos la matriz de origen, su largo y ancho a la funcion que imprime matrices.
    printf("\n");
    matriz_par(p, n, s); //Llamada a la funcion que modifica la matriz generada a matriz par.
}


void matriz_par(unsigned int **p, int n, float s)
{   
    int root, i = 0, j = 0, h = 0, c = 0, x = 0, l = 0, cont = 1, cont1 = 0, posicion, resto = 0, inicio, fin; //Se inicializan las vainicio, fin;riables de tipo int que seran utilizadas.
    inicio = clock();   //Variable que comienza a tomar el tiempo de ejecucion del programa.
    cont = 0;   //Se inicializa la variable cont en 0.
    posicion = 0;   //Se inicializa la variable posicion en 0.
    for(i = 0; i < n; i = i + 1)    //For que recorre filas de la matriz hacia abajo.   
    {
        for (j = 0; j < n; j = j + 1)   //For que recorre fila de la matriz hacia la derecha.
        {       
            if (p[i][j] == 1)   //Si el vertice ya tiene una arista, hacer lo siguiente.
                p[j][i] = 1;    //Se situa en la posicion de la matriz segun el recorrido y agrega la arista al nodo para que el grafo sea no dirigido.
        }
    }
    for(i = 0; i < n; i = i + 1)    //For que recorre fila de la matriz.    
    {
        for (j = i + 1; j < n; j = j + 1)   //For que recorre columna de la matriz.
        {       
            if (j == i + 1) //Si el indice j es igual al indice i + 1, que recorre la matriz hacia abajo, se realiza lo siguiente. 
            {
                p[i][j] = 1;    //Se situa en la posicion de la matriz segun el recorrido y agrega la arista al nodo para que el grafo sea no dirigido.
                p[j][i] = 1;    //Se situa en la posicion de la matriz segun el recorrido y agrega la arista al nodo para que el grafo sea no dirigido.
            }   
        }
    }
    for (i = 0; i <n; i = i + 1) //For que recorre filas de la matriz hacia abajo.      
    {
        cont = 0;   //Variable cont se inicializa en 0.
        for (j = 0; j < n; j = j +1)    //For que recorre fila de la matriz hacia la derecha.   
        {
            if (p[i][j] == 1)   //Si en la fila recorrida hay alguna arista, se realiza lo siguiente.
            {
                cont = cont + 1;    //Se suma 1 a contador, que tendra la cantidad de aristas en el vertice situado.
            }
            if (j == n - 1) //Cuando el vertice sea recorrido completamente, se realiza lo siguiente.
            {
                resto = cont%2; //Se almacena en la variable resto el resultado del modulo 2 de la variable contador.
                if (resto == 0) //Si el vertice tiene cantidad par de aristas, se realiza lo siguiente.
                {
                    cont1 = cont1 + 1;  //Se suma 1 a la variable cont1, que posee la cantidad de vertices pares que contiene el grafo.
                }
            }

        }
        if (i == n-1)   //Cuando se terminan de recorrer todos los vertices del grafo, se realiza lo siguiente.
        {
            if (cont1 == n) //Si el grafo finalmente es par (todos sus vertices son pares), se realiza lo siguiente.
            {
                float tiempo = 0;
                FILE *file;
                pila *ciclo = NULL;
                printf("El Grafo conexo no-dirigido simple y de grado par generado es: \n\n");  //Se imprime por pantalla el mensaje.
                getchar();
                print(p,n); //Se muestra por pantalla el grafo aleatorio conexo no-dirigido simple y par./
                printf("\n Un ciclo de euler corresponde a: \n");
                ciclo = euler(n, p);
                showeuler(ciclo);
                printf("\n");
                fin = clock();
                tiempo = (fin-inicio)/(double)CLOCKS_PER_SEC;
                printf("\nEl tiempo de ejecución fue de: %F \n\n",tiempo);  //Se imprime el tiempo de ejecucion.
                file = fopen("lab03exp.txt", "a");
                if(file == NULL)
                {
                    printf("Error al abrir el archivo\n");
                }
                fprintf(file,"Dimensión matriz: %d Probabilidad: %f Tiempo total: %f \n",n, (s/100), tiempo);
                fclose(file);   
                exit(0);
            }
        }
    }
    for(i = 0; i < n; i = i + 1)    //For que recorre filas de la matriz hacia abajo.   
    {   
        posicion = 0;   //Posicion se inicializa en 0.
        cont = 0;   //Contador se inicializa en 0.
        for (j = 0; j < n; j = j + 1)   //For que recorre fila de la matriz hacia la derecha.
        {
            if (i == j) //Condicion que no permite vertices con lazos.
            {
                p[i][j] = 0;    //Se agrega un 0 a la posicion.
            }
            if (p[i][j] == 1)   //Si el vertice contiene arista, se hace lo siguiente.
                cont = cont + 1;    //contador aumenta en 1.
            if (j == n - 1) //Si se termina de recorrer la fila, se hace lo siguiente.
            {
                if (cont % 2 != 0)  //Si se encuentra un vertice impar, s realiza lo siguiente.
                {
                    for (h = i + 1; h < n; h = h + 1)   //Se avanza hacia la fila siguiente.
                    {
                        cont = 0;   //contador vuelve a ser 0.
                        for (c = 0; c < n; c = c + 1)   //Se recorre la fila elemento por elemento.
                        {   
                            if (p[h][c] == 1)   //Si el vertice tiene arista, se realiza lo siguiente.
                                cont = cont + 1;    //Contador aumenta en 1.
                            if (c == n - 1) //Si se termina de recorrer la fila siguiente, se hace lo siguiente.
                            {
                                resto = cont%2; //Se almacena en la variable resto el resultado del modulo 2 de la variable contador.
                                if (resto != 0) //Si el vertice tiene cantidad impar de aristas, se realiza lo siguiente.
                                {
                                    if (p[h][i] == 0)   //Si en los vertices situados no hay arista, se realiza lo siguiente. 
                                    {
                                        p[h][i] = 1;    //Se agrega la arista entre los vertiiices.
                                        p[i][h] = 1;    //Se agrega la arista entre los vertices.
                                    }
                                    else    //De no ser asi...
                                    {
                                        if (p[h][i] == 1 && posicion == 1)  //Si en los vertices situados hay conexion, pero no es su vertice continuo, se realiza lo siguiente.
                                        {
                                            p[h][i] = 0;    //Se elimina la arista entre los vertices.
                                            p[i][h] = 0;    //Se elimina la arista entre los vertices.
                                        }
                                        else    //De no ser asi...
                                        {
                                            if (p[h][i] == 1 && posicion == 0)  //Se en los vertices situados hay conexion, pero los vertices son continuos, se realiza lo siguiente.
                                            {
                                                h = 1;  //h se inicializa en 1.
                                                if (i-2 >= 0)   //Si en el grafo existe el vertice c que este 2 espacios atras que a, se realiza lo siguiente.
                                                {
                                                    if (p[i][h+1] == 0) //Se invierten los valores de los vertices (a,c) y (c,b) para tal caso.
                                                    {
                                                        p[i][h+1] = 1;
                                                    }
                                                    else
                                                    {
                                                        p[i][h+1] = 0;
                                                    }
                                                    if (p[i+1][h+1] == 0)
                                                    {
                                                        p[i+1][h+1] = 1;
                                                    }
                                                    else
                                                    {
                                                        p[i+1][h+1] = 0;
                                                    }
                                                    if (p[i-2][h] == 0)
                                                    {
                                                        p[i-2][h] = 1;
                                                    }
                                                    else
                                                    {
                                                        p[i-2][h] = 0;
                                                    }
                                                    if (p[i-2][h-1] == 0)
                                                    {
                                                        p[i-2][h-1] = 1;
                                                    }
                                                    else
                                                    {
                                                        p[i-2][h-1] = 0;
                                                    }
                                                }
                                                if (i-2 < 0)    //Si en el grafo existe el vertice c que este 2 espacios adelante que a, se realiza lo siguiente.
                                                {
                                                    if (p[i][h+1] == 0) //Se invierten los valores de los vertices (a,c) y (c,b) para tal caso.
                                                    {
                                                        p[i][h+1] = 1;
                                                    }
                                                    else
                                                    {
                                                        p[i][h+1] = 0;
                                                    }
                                                    if (p[i+1][h+1] == 0)
                                                    {
                                                        p[i+1][h+1] = 1;
                                                    }
                                                    else
                                                    {
                                                        p[i+1][h+1] = 0;
                                                    }
                                                    if (p[i+3][h-1] == 0)
                                                    {
                                                        p[i+3][h-1] = 1;
                                                    }
                                                    else
                                                    {
                                                        p[i+3][h-1] = 0;
                                                    }
                                                    if (p[i+3][h] == 0)
                                                    {
                                                        p[i+3][h] = 1;
                                                    }
                                                    else
                                                    {
                                                        p[i+3][h+1] = 0;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        posicion = 1;   //La variable posicion cambia a 1.
                    }
                }
            }
        }
    }
    matriz_par(p,n,s);  //Se vuelve a llamar a la funcion, para verificar si el Grafo es conexo no-dirigido simple y de grado par, de no ser asi, se realizan los mismos pasos.
}

//Función que encuentra un ciclo de Euler, si al recorrer todos los vértices posibles de la matriz
//encuentra un ciclo cerrado (todas las aristas recorridas y terminar en el vértice inicial) hay un ciclo de Euler.
pila* euler(int n, int unsigned **p)
{
    int i, j, arista = 0;
    pila *ciclo = NULL;
    pila *path = NULL;
    for (i = 0; i < n; i++) // Se cuenta el total de aristas del grafo.
    {
        for (j = i+1; j < n; j++)
            if (p[i][j])
                arista++;
    }   
    //Se guarda el camino recorrido en la pila de 'path'
    i = 0;
    i = v_cercano(n, p[i]); 
    path = push(path, 0);
    path = push(path, i);
    p[0][i] = 0;
    p[i][0] = 0;
    arista--;
    while(arista > 0)
    {
        if(count_a(p[i], n) > 0) // Si se encuentra un vertice adyacente, se agrega al camino ('path').
        {
            j = v_cercano(n, p[i]);
            path = push(path, j);
        }   
        else //Si no se encuentran vértices para moverse, buscamos en los vértices del camino recorrido ('path').
        {
            while(count_a(p[path->dest], n) == 0) //Los vértices sin aristas hacen pop en la pila.
            {
                ciclo = push(ciclo, path->dest); 
                path = pop(path);
            }
            i = path->dest;
            j = v_cercano(n, p[i]); //El primer vértice más cercano encontrado queda como actual.
            path = push(path, j);
        }
        p[i][j] = 0; //Se eliminan las aristas, para que no sean consideradas, siendo ya contadas en el ciclo de Euler.
        p[j][i] = 0;
        arista--;
        i = j;
    }
    while(path) //Si quedan vertices en el camino ('path') se agregan a la pila del ciclo de Euler y se eliminan de la pila 'path'.
    {
        ciclo = push(ciclo, path->dest);
        path = pop(path);
    }
    return ciclo;
}

//Función que retorna el primer vértice cercano que encuentra al vértice correspondiente-
int v_cercano(int n, int vertices[])
{
    int i;
    for (i = 0; i < n; i++)
        if (vertices[i] == 1)
            return i;
    return -1;
}

//Función que recorre una fila y cuenta los vértices que se encuentran cercanos a ese vértice
int count_a(int vertice[], int n)
{
    int i, k=0;
    for (i = 0; i < n; i++)
        if (vertice[i] == 1)
            k++;
    return k;
}