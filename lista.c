#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


/*****
*
TipoFunción NombreFunción : constructor
******
*
Resumen Función : inicializa una lista vacia
******
*
Input: sin parametro
tipoParámetro NombreParámetro
*
.......
******
*
Returns: tLista*
TipoRetorno, Descripción retorno : retorna un puntero l a una lista inicializada
*****/


tLista* constructor() {
    tLista* l;
    l = (tLista*)malloc(sizeof(tLista));
    l->head = l->tail = l->curr = (tNodo *)malloc(sizeof(tNodo));
    l->pos = 0;
    l->listSize = 0;
    return l;
}

/*****
*
TipoFunción NombreFunción : destructor
******
*
Resumen Función : funcion que destruye lista haciendo free de esta
******
*
Input: puntero a lista
tipoParámetro NombreParámetro : tLista* l
*
.......
******
*
Returns: void
*****/

void destructor(tLista* l) {
    free(l);
}


/*****
*
TipoFunción NombreFunción : length
******
*
Resumen Función : funcion que regresa el tamaño de la lista
******
*
Input: puntero de tipo lista
tipoParámetro NombreParámetro : tLista* l
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : retorna int, el retorno indica el tamaño de la lista
*****/


int length(tLista* l) {
    int x;
    x = l->listSize;
    return x;
}



/*****
*
TipoFunción NombreFunción : moveToEnd
******
*
Resumen Función : funcion que mueve el current al final de la lista
******
*
Input: puntero de tipo lista
tipoParámetro NombreParámetro : tLista* l
*
.......
******
*
Returns: void
*****/



void moveToEnd(tLista* l) {
    if(l->curr != l->tail){
        l->curr = l->tail;
        l->pos = l->listSize-1;
    }
}


/*****
*
TipoFunción NombreFunción : moveToStar
******
*
Resumen Función : funcion que mueve el current al inicio de la lista
******
*
Input: puntero de tipo lista
tipoParámetro NombreParámetro : tLista* l
*
.......
******
*
Returns: void
*****/


void moveToStar(tLista* l) {
    if (l->head != NULL){
        l->curr = l->head;
        l->pos = 0;
    }
}


/*****
*
TipoFunción NombreFunción : moveToPos
******
*
Resumen Función : funcion que mueve el current a una posicion especificada de la lista
******
*
Input: puntero de tipo lista ;  entero que indica la posicion de la lista a la que se quiere mover el current
tipoParámetro NombreParámetro : tLista* l ; int posicionN
*
.......
******
*
Returns: void
*****/

void moveToPos (tLista* l, int posicionN) {
    if (posicionN < l->listSize){
        if (l->pos != posicionN){
            if (l->pos < posicionN){  //si la posicion actual es menor a la que busco
                while (l->pos < posicionN) {
                    l->pos+=1;
                    if (l->curr->sig != NULL) {
                        l->curr = l->curr->sig;
                    }
                    else{
                        l->curr = l->tail;
                    }
                }

            }
            else {
                moveToStar(l);
                while (l->pos < posicionN) {
                    l->curr = l->curr->sig;
                    l->pos+=1;
                }
            }
        }
    }
}


/*****
*
TipoFunción NombreFunción : append1
******
*
Resumen Función : funcion que agrega elemento al final de la lista
******
*
Input: puntero de tipo lista ;  entero que contiene la info1 del nodo a agregar ; entero que contiene la info2 del nodo a agregar
tipoParámetro NombreParámetro : tLista* l ; int item1 ; int item2
*
.......
******
*
Returns: void
*****/

void append1(tLista* l, int item1) {
    int x;
    x = l->pos;

    if(l->listSize == 0){ //revisa si el tamaño de la lista igual a 0
        l->curr->info1 = item1;
        //printf("ELEMENTO AGREGADO %d\n", item1);
        l->listSize++;
    }
    else{
        moveToEnd(l); // mueve el current al final
        l->curr->sig = (tNodo *)malloc(sizeof(tNodo)); // reservo memoria para la casilla final
        l->tail = l->curr->sig; // ahora el tail apunta una posicion mas que el current
        l->listSize++;   // aumento el tamaño de la lista en 1
        l->tail->info1 = item1; //  a la casilla de info del nodo apuntado por tail le guardo el item a insertar
        moveToPos(l,x);
    }
}

/*****
*
TipoFunción NombreFunción : GetPos
******
*
Resumen Función : funcion que regresa la posicion actual de la lista
******
*
Input: puntero de tipo lista
tipoParámetro NombreParámetro : tLista* l
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : retorna int, el retorno indica la posicion actual de la lista
*****/

int GetPos(tLista* l) {
    int a;
    a = l->pos;
    return a;
}

/*****
*
TipoFunción NombreFunción : GetValue
******
*
Resumen Función : funcion utilizada para acceder a la info1 del struct nodo
******
*
Input: puntero de tipo lista ;  entero con la posicion del nodo a revisar
tipoParámetro NombreParámetro : tLista* l ; int pos
*
.......
******
*
Returns:
TipoRetorno, Descripción retorno : retorna int, el retorno es la info1 del nodo en cuestion
*****/

int GetValue(tLista* l) {
    int a;
    a = l->curr->info1;
    return a;
}

/*****
*
TipoFunción NombreFunción : insert1
******
*
Resumen Función : inserta un elemento en la posición actual de la lista, no sirve para insertar en listas vacias (se debe usar append1 para ese caso)
******
*
Input: puntero de tipo lista ;  entero con info1 del nodo a insertar ; entero con info2 del nodo a insertar
tipoParámetro NombreParámetro : tLista* l ; int item1 ; int item2
*
.......
******
*
Returns:void
*****/


void insert1(tLista* l, int item1, int item2) {
    int x;
    x = l->pos;

    if (l->curr == l->head){
        tNodo* aux = l->head;
        l->head = (tNodo *)malloc(sizeof(tNodo));
        l->head->info1 = item1;
        l->head->sig = aux;
        l->listSize++;
    }

    else {
        tNodo* aux = l->curr->sig;
        l->curr->sig = (tNodo *)malloc(sizeof(tNodo));
        l->curr->sig->info1 = item1;
        l->curr->sig->sig = aux;
        if (l->curr == l->tail){
            l->tail = l->curr->sig;
        }
        l->listSize++;
    }
    moveToPos(l,x);
}


/*****
*
TipoFunción NombreFunción : remove1
******
*
Resumen Función : funcion utilizada para eliminar el nodo actual
******
*
Input: puntero de tipo lista
tipoParámetro NombreParámetro : tLista* l
*
.......
******
*
Returns: void
*****/

void remove1(tLista* l) {
    int nodoAnterior;
    tNodo* aux = l->curr;

    if(l->curr == l->head){
        aux = l->curr->sig;
        free(l->curr);
        l->head = aux;
        l->curr = aux;
    }

    else{
        nodoAnterior = l->pos-1;
        moveToPos(l,nodoAnterior);
        if (l->curr->sig == l->tail){
            l->tail=l->curr; // *
        }

        l->curr->sig = l->curr->sig->sig;
        free(aux);

    }
    l->listSize--;

}

/*****
*
TipoFunción NombreFunción : clear
******
*
Resumen Función : funcion utilizada para borrar los elementos de la lista y reiniciarla vacia
******
*
Input: puntero de tipo lista
tipoParámetro NombreParámetro : tLista* l
*
.......
******
*
Returns: void
*****/

void clear(tLista* l) {
    tNodo* aux;
    int i;

    if (l->listSize == 0){
        return;
    }
    moveToStar(l);

    for (i=0; i < l->listSize; ++i){
        aux = l->curr->sig;
        free(l->curr);
        l->curr = aux;

    }

    l->pos = 0;
    l->listSize = 0;
    l->head = l->curr = l->tail = (tNodo *)malloc(sizeof(tNodo));;

}


/*****
*
TipoFunción NombreFunción : update
******
*
Resumen Función : funcion utilizada para actualizar info1 del nodo actual de la lista1 con memoria disponible una vez ejecutado el malloc
******
*
Input: puntero de tipo lista ;  entero que informa el nuevo byte de inicio de memoria disponible en la lista1
tipoParámetro NombreParámetro : tLista* l ; int new
*
.......
******
*
Returns: void
*****/

void update(tLista* l, int new) { //actualiza el curr //FUNCION

    l->curr->info1 = new;
    
}


//
// Funcion que busca un elemento en la lista, 
// si lo encuentra retorna la pos donde se encuentra
//
int elementChecker(tLista* l, int element) {
    int largo, i, x, pos;
    largo = length(l);
    pos = l->pos;

    for (i=0; i < largo; ++i){
        moveToPos(l,i);
        x = GetValue(l);
        if (x == element) {
            moveToPos(l,pos);  
            return i;
        }
    }
    moveToPos(l,pos);  
    return (-1);  
}


// Funcion que recibe dos listas,
// siuno hay existe algun numero 
// que esté en ambas listas, retorna un
// -1, cc retorna un 1
//
int compararListas(tLista* l1, tLista* l2) {
    int s1, s2, i1, i2, e1, e2;
    s1 = length(l1);
    s2 = length(l2);
    for (i1 = 0; i1 < s1; i1++) {
        moveToPos(l1, i1);
        e1 = GetValue(l1);
        for (i2 = 0; i2 < s2; i2++) {
            moveToPos(l2, i2);
            e2 = GetValue(l2);
            if (e2 == e1) {
                return (-1);  // conflicto
            }
        }
    }
    return 1;
}


void PrintLista(tLista* l) {
    int x, i, pos;
    pos = l->pos;
    //printf("POS %d\n", pos);
    printf("-------------------\n");
    printf("IMPRIMIENDO LISTA \n");
    for (i=0; i < l->listSize; ++i){
        moveToPos(l,i);
        x = GetValue(l);
        printf("%d\n",x);
    }
    printf("-------------------\n");
    moveToPos(l,pos);    
}