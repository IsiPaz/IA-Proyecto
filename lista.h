#ifndef _LISTA_H_
#define _LISTA_H_


typedef struct tNodo {
    int info1;
    struct tNodo *sig;
} tNodo;


typedef struct {
    tNodo* head;
    tNodo* tail;
    tNodo* curr;
    int listSize;
    int pos;
} tLista;

tLista* constructor();
void destructor(tLista* l);
int length(tLista* l);
void moveToEnd(tLista* l);
void moveToStar(tLista* l);
void moveToPos (tLista* l, int posicionN);
void append1(tLista* l, int item1);
int GetPos(tLista* l);
int GetValue(tLista* l);
void insert1(tLista* l, int item1, int item2);
void remove1(tLista* l);
void clear(tLista* l);
void update(tLista* l, int new);
int elementChecker(tLista* l, int element);
int compararListas(tLista* l1, tLista* l2);
void PrintLista(tLista* l);

#endif