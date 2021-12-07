#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "lista.h"

// String a Entero
int stringToInt (char* numero) {
    int x = atoi(numero);
    printf("Converting %s : %d\n", numero, x);
    return x;
}

// Entrega un float random en entre min y max
float float_rand( float min, float max ){
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

// Entrega las penalizaciones segun el timeslot x e y
int Score(int x, int y) {
    int resta = abs(x - y);
    if (resta == 1){
        return 16;
    }
    if (resta == 2){
        return 8;
    }
    if (resta == 3){
        return 4;
    }
    if (resta == 4){
        return 2;
    }
    if (resta == 5){
        return 1;
    }
    else {
        return 0;
    }
}

// Entrega randoms int entre inf y sup 
int IntRandoms(int inf, int sup) {
    int num = (rand() % (sup - inf + 1)) + inf;
    return num;   
}


int ContarFilasZERO(int** matriz, int x, int y) {
    int zero = 0;
    int flag, flag1;
    int comienza = 0;
    flag1 = 0;
    for (int a = 0; a < x; a++) {
        flag = -1; // 1 : vi un 1, -1 : no vi un 1
        for (int b = 0; b < y; b++) {
            if (matriz[a][b] == 1) {
                b = y;
                flag = 1;
            }
        }        
        if (flag == -1) { // si no hay unos en la fila 
            zero = zero + 1;
            if (flag1 == 0) {
                flag1 = 1;
                comienza = a;
            }
        }
    }
    return comienza;
}

// Genera una copia de la matriz original
int** CopiarMatriz (int** original, int a, int b) {
    int x;
    int** matriz = (int **)calloc(a,sizeof(int*));

    for(x=0; x<a; x++) {
        matriz[x] = (int *)calloc(b, sizeof(int));
    }
    for(x=0;x<a; x++) {
        for(int y = 0; y<b; y++) {
            matriz[x][y] = original[x][y];
        }
    }
    return matriz;
}


// Retorna la cantidad de alumnos que tiene el archivo .stu
// tiene que recibi el char con el nombre del archivo cursos
int obtenerAlumnos (char *archi_alumno){  
    FILE *fp;
    char studentID[10];
	int examenID, r, y;
	
	fp = fopen(archi_alumno, "rt");
	if (fp == NULL) { 
		printf("No se pudo abrir el archivo Alumnos\n"); 
    }

	while ((r = fscanf(fp, "%s %d", studentID, &examenID)) != EOF) {
	}

    char *b = studentID + 1;
    
    y = atoi(b); // Using atoi()
    fclose(fp);

    return y;
}

// Retorna la cantidad de examenes en el archivo .exm
// tiene que recibi el char con el nombre del archivo cursos
int obtenerExamenes (char *archi_examen){  
    FILE *fp;
    int n = 50;
    char str[n];
    int cant = 0;

    fp = fopen(archi_examen, "r");   // aqui abro el archivo de cursos :D

    if (fp == NULL) {
        printf ("No es posible abrir el archivo %s para su lectura\n" , archi_examen);
    }

    while (feof(fp) == 0) {
        if( fgets (str, n, fp)!=NULL ) {
            cant = cant + 1;
        }
    }

    fclose(fp);

    return cant;
}

// Genera la matriz a X b inicilizada en ceros
int** CrearMatriz (int a, int b) {
    int x;
    int** matriz = (int **)calloc(a,sizeof(int*));

    for(x=0; x<a; x++) {
        matriz[x] = (int *)calloc(b, sizeof(int));
    }

    return matriz;
}

// Funcion que imprime la matriz a x b
void imprimirMatriz(int **matriz, int a, int b) {
    //Función auxiliar para imprimir la matriz de conflicto.
    int x,y;

    for (x=0;x<a;x++){
        for (y=0;y<b;y++){	
                printf("| %d |",matriz[x][y]);							
        }
        printf("\n\n\n");
    }
}

// Funcion que regresa la matriz que indica los examenes que cada alumno rinde
int** AsignarEA(int cant_alumnos, int cant_examenes, char *archi_alumno ) {

    int** matriz;
    matriz = CrearMatriz(cant_alumnos,cant_examenes);

    //archivo
    FILE *fp;
    char studentID[10];
	int examenID, r;

    char ultimo_visto[] = "first"; // char que almacena el ultimo ID de estudiante revisado
    int contador_de_pruebas = 0;   // contador para la cantidad de pruebas que da cada estudiante
    int contador_alumno = 0;

    tLista *lista1;  // lista enlazada que almacena las pruebas de cada alumno
    lista1 = constructor();

	fp = fopen(archi_alumno, "rt");
	if (fp == NULL) { 
		printf("No se pudo abrir el archivo"); 
    }

	while ((r = fscanf(fp, "%s %d", studentID, &examenID)) != EOF) {
	    if (r == 2) { // Do we get the two matches of "%d %d"?|
		    //printf("studentID value: \t\t%s\n", studentID);
		    //printf("ExamenID value: \t\t%d\n\n", examenID);
            
            if (strcmp(ultimo_visto, studentID) != 0 ) { // Si no se ha visto previamente un alumno
                //printf("FLAG 2\n");
                if (contador_de_pruebas != 0) {   // si la lista tiene elementos
                    int valor;
                    int a = 0;
                    while (a < contador_de_pruebas) {  // RELLENAR LA MATRIZ 
                        moveToPos(lista1, a);
                        valor = GetValue(lista1);
                        matriz[contador_alumno][valor-1] = 1; 
                        a = a + 1;
                        //printf("FLAG 9\n");
                    }
                    contador_alumno = contador_alumno + 1;        
                    clear(lista1);
                    contador_de_pruebas = 0;
                }
            
                // Se agrega elementos a la lista vacia
                strcpy(ultimo_visto, studentID);
                append1(lista1,examenID);
                contador_de_pruebas = contador_de_pruebas + 1;
            }

            else { // si es el mismo estudiante que ultimo_visto, se agrega simplemente a la lista
                append1(lista1, examenID);
                contador_de_pruebas = contador_de_pruebas + 1;
            }
	    }
	}

    int a = 0;
    while (a < contador_de_pruebas) {
        moveToPos(lista1, a);
        int valor = GetValue(lista1);
        matriz[contador_alumno][valor-1] = 1;    
        a = a + 1;     
    }

    //printf("------------------------MATRIZ ALUMNOS Y EXAMENES------------------------\n");
    //imprimirMatriz(matriz, cant_alumnos,cant_examenes);
    clear(lista1);
    free(lista1);
    fclose(fp);
    return matriz;
}

// Funcion que recibe una matriz simetrica inicializada con ceros,
// esta matriz es la matriz de conflictos y retorna la matriz con los conflictos
// archi_alumno es el nombre del archivo de alumnos .stu 
int** FillMatriz(int **matriz, char *archi_alumno, int cant_examenes) {

    FILE *fp;
    char studentID[10];
	int examenID, r;

    char ultimo_visto[] = "first"; // char que almacena el ultimo ID de estudiante revisado
    int contador_de_pruebas = 0;   // contador para la cantidad de pruebas que da cada estudiante

    tLista *lista1;  // lista enlazada que almacena las pruebas de cada alumno

	//printf("FLAG 1\n");
	fp = fopen(archi_alumno, "rt");
	if (fp == NULL) { 
		printf("No se pudo abrir el archivo"); 
    }

    lista1 = constructor();
	while ((r = fscanf(fp, "%s %d", studentID, &examenID)) != EOF) {
	    if (r == 2) { // Do we get the two matches of "%d %d"?|
            if (strcmp(ultimo_visto, studentID) != 0 ) { // Si no se ha visto previamente un alumno
                if (contador_de_pruebas != 0) {   // si la lista tiene elementos
                    if (length(lista1) > 1){ // REVISAR SI TIENE MAS UN ITEM
                        int valor, valor1;
                        int a = 0;
                        while (a < contador_de_pruebas) {  // RELLENAR LA MATRIZ
                            moveToPos(lista1, a);
                            int b = a+1;
                            valor = GetValue(lista1);
                            while (b < contador_de_pruebas) {
                                moveToPos(lista1,b);
                                valor1 = GetValue(lista1);;
                                // RELLENAR LA MATRIZ 
                                matriz[valor-1][valor1-1] = 1;
                                matriz[valor1-1][valor-1] = 1;
                                b = b + 1;
                            }
                            a = a + 1;
                        }
                        // LIMPIAR LA LISTA
                        clear(lista1);
                        contador_de_pruebas = 0;
                    }
                    // SI TIENE UN OBJETO SE LIMPIA LA LISTA PORQUE NO HAY CONFLICTOS
                    else {
                        // LIMPIAR LA LISTA
                        clear(lista1);
                        contador_de_pruebas = 0;
                    }
                }
                
                // Se agrega elementos a la lista vacia
                strcpy(ultimo_visto, studentID);
                //printf("ULTIMO VISTO: %s\n", ultimo_visto);
                
                append1(lista1,examenID);
                contador_de_pruebas = contador_de_pruebas + 1;
            }

            else { // si es el mismo estudiante que ultimo_visto, se agrega simplemente a la lista
                append1(lista1, examenID);
                contador_de_pruebas = contador_de_pruebas + 1;
            }
	    }
	}

    //printf("------------------------MATRIZ CONFLICTOS------------------------\n");
    //imprimirMatriz(matriz, cant_examenes,cant_examenes);
 
    clear(lista1);
    free(lista1);

    fclose(fp);
    return matriz;
}


// Funcion que encuentra la cantidad de timeslots max a utilizar por greedy
int EncontrarTSM (int** matrix, int cantExam) {
    int x, y, timeslotMAX, ts;

    tLista* ListaIngresados;
    ListaIngresados = constructor();
    timeslotMAX = 0;
    
    for (x = 0; x < cantExam; x++) {
        ts = 0;
        //RECORREMOS LA MATRIZ PARA GENERAR UN VECTOR DE CONFLICTO
        for (y = 0; y < cantExam; y++) {
            if (matrix[x][y] == 1){
                if (elementChecker(ListaIngresados, y+1) == -1) { // si el elemento no esta en la lista            
                    append1(ListaIngresados, y+1);                
                    ts = ts + 1;
                }
                if (ts > timeslotMAX){
                    timeslotMAX = ts;
                }
            }
        }
    }
    clear(ListaIngresados);
    free(ListaIngresados);
    return timeslotMAX+1;
}

// Algoritmo greedy que devuelve la solución inicial
int** Greedy(int** matrix, int cantExam, int* tsm) {

    int TSM, i, w, y, z;
    TSM = EncontrarTSM(matrix, cantExam);
    *tsm = TSM;

    tLista* soluciones[TSM];
    tLista* conflictos;

    int** matrizsol;
    matrizsol = CrearMatriz(TSM, cantExam);

    for (i=0; i < TSM; i++ ){
        tLista* listita;
        listita = constructor();
        soluciones[i] = listita;
    }

    conflictos = constructor();
    

    for (y = 0; y < cantExam; y++) {
        for (w = 0; w < cantExam; w++) {
            if (matrix[y][w] == 1){
                append1(conflictos, w+1);
            }
        }

        for (z = 0; z < TSM; z++){
            if (elementChecker(soluciones[z], y+1) == -1){
                if (compararListas(soluciones[z], conflictos) == 1) {
                    append1(soluciones[z], y+1);
                    matrizsol[z][y] = 1;
                    z = TSM;
                }
            }
        }
        clear(conflictos);    
    }

    clear(conflictos);
    free(conflictos);

/*     for (i = 0; i < TSM; i++){
        printf("TIMESLOT: %d\n", i+1);
        PrintLista(soluciones[i]);
    } */

    for (i = 0; i < TSM; i++){
        clear(soluciones[i]);
        free(soluciones[i]);
    }
    printf("------------------------MATRIZ SOLUCION GREEDY------------------------\n");
    imprimirMatriz(matrizsol, TSM, cantExam);

    return matrizsol;
}


float EvaluarCalidad (int** matrixAE, int** matrix, int cant_alumnos, int cant_examenes, int timeslotMAX) {

    int i2, v1, v2;
    int x = 0;
    int y = 0;
    int penalizacion_promedio = 0;
    int penalizacion_alumno = 0;

    tLista* pruebas;
    pruebas = constructor();
    // Recorre la matriz de Alumnos-Examenes
    for (x = 0; x < cant_alumnos; x++) {
        penalizacion_alumno = 0;
        for (y = 0; y < cant_examenes; y++) { 
            if (matrixAE[x][y] == 1) {
                append1(pruebas, y); // se agregan las pruebas del alumno x a la lista
            }   
        }
        for (int i1 = 0; i1 < length(pruebas); i1++) { // recorre la lista de examenes que rinde el alumno x
                        
            i2 = i1+1;
            if (i2 > length(pruebas)){
                i1 = length(pruebas); // para no leer fuera del arreglo
            }
            else {
                moveToPos(pruebas, i1);
                int value1 = GetValue(pruebas);
                moveToPos(pruebas, i2);
                int value2 = GetValue(pruebas);
                
                for (int timeslot1 = 0; timeslot1 < timeslotMAX; timeslot1++) {
                    if (matrix[timeslot1][value1] == 1) {
                        v1 = timeslot1;
                        timeslot1 = timeslotMAX;
                    }
                }
                for (int timeslot2 = 0; timeslot2 < timeslotMAX; timeslot2++) {
                    if (matrix[timeslot2][value2] == 1) {
                        v2 = timeslot2;
                        timeslot2 = timeslotMAX;
                    }
                }
                
                penalizacion_alumno = penalizacion_alumno + Score(v1,v2);
                //printf("Penalizacion alumno x %d es de %d\n", x+1, penalizacion_alumno);
                
            }
        }
        clear(pruebas);
        penalizacion_promedio = penalizacion_promedio + penalizacion_alumno;

    }
    free(pruebas);
    return penalizacion_promedio/cant_alumnos;
}


// matrix =  matriz de -X-
// conflicto = matriz simetrica de -X-
int** Movimiento(int** matrix, int** conflictos, int cant_exam, int cant_alum, int timeslots) {

    int examen, i, a, u, e, actualTS;
    tLista* conflicto;
    tLista* agendados;

    examen = IntRandoms(0,cant_exam-1);
    conflicto = constructor();
    agendados = constructor();

    // Encontrar el timeslot actual en el que se encuentra agendado el examen
    for (e = 0; e < timeslots; e++){
        if(matrix[e][examen] == 1){
            actualTS = e;
            e = timeslots;
        }
    }

    // Lista de conflictos para examen elegido random
    for (i = 0; i < cant_exam; i++) {
        if (conflictos[examen][i] == 1){
            append1(conflicto,i);
        }
    }
    for (a = 0; a < timeslots; a++) {
        // generar lista de examenes agendados en el timeslot a
        for(u = 0; u < cant_exam; u++) {
            if (matrix[a][u] == 1){
                append1(agendados,u);
            }
        }
        if (compararListas(conflicto,agendados) == 1  && a != actualTS) { // No existe conflicto
            // se puede realizar el cambio
            matrix[actualTS][examen] = 0;
            matrix[a][examen] = 1;
            break;
        }

        clear(agendados);
    }
    clear(conflicto);
    clear(agendados);
    free(conflicto);
    free(agendados);
    return matrix;
}  




int** SimulatedAnnealing(int** matrixG, int** matrixAE, int** matrixC, float alpha, int cant_alumnos, int cant_examenes, int ts, int mejoras) {

    float MejorCal = EvaluarCalidad(matrixAE, matrixG, cant_alumnos, cant_examenes, ts);  // f(Sbest)
    float calidad = MejorCal; // f(Sc)

    printf("calidad inicial pre SA: %f \n", MejorCal);

    int** MejorSol;
    int** NewMatriz;    // Sn
    int** Actual;

    int** matriz_para_cambiar;
    matriz_para_cambiar = CopiarMatriz(matrixG, ts, cant_examenes);

    MejorSol = matrixG; // Sbest -> Sc
    Actual = matriz_para_cambiar;   // Sc

    float calidadN; // Sn
    
    int t = 0;
    int T = 24;
    

    for (int i = 0; i < 5; i++) {
        for (int it = 0; it < mejoras; it++) {
            NewMatriz = Movimiento(Actual, matrixC, cant_examenes, cant_alumnos, ts);        // 
            calidadN = EvaluarCalidad(matrixAE, NewMatriz, cant_alumnos, cant_examenes, ts); // f(Sn)
            if (calidadN > calidad) {
                Actual = NewMatriz;
                calidad = calidadN;
            }
            else if (float_rand(0.0,1.0) < exp((calidadN-calidad)/T)) {
                Actual = NewMatriz;
                calidad = calidadN;
            }
            if (calidad > MejorCal) {
                MejorCal = calidad;
                MejorSol = Actual;
            }
        }
        T = T*alpha;
        t = t + 1;
    }

    printf("calidad final post SA: %f \n", MejorCal);
    int cortar;
    cortar = ContarFilasZERO(MejorSol,ts,cant_examenes);
    printf("SA TIMESLOTS: %d \n", ts-cortar);

    printf("------------------------MATRIZ SOLUCION SA------------------------\n");
    imprimirMatriz(MejorSol,cortar-1,cant_examenes);

    return MejorSol;
}

 



// INSTANCIAS
// St.Andrews83
// test
// TorontoE92

int main () {
    
    int cant_alumnos, cant_examenes, tsm;
    int** matrixC;
    int** matrizSol;
    int** matrixAE;
    int** matrixSA;

    //float calidad;

    char buff[20];
    char stu[20];
    char exm[20];



    printf("Ingrese el nombre de archivo sin extensión\n");
    scanf("%s", buff);
    strcat(strcpy(stu, buff), ".stu");
    strcat(strcpy(exm, buff), ".exm");

    cant_alumnos = obtenerAlumnos(stu);         // Cantidad de alumnos
    cant_examenes = obtenerExamenes(exm);       // Cantidad de examenes

    printf ("\n");
    printf ("Cantidad de Examenes %d \n" , cant_examenes);
    printf ("Cantidad de Alumnos %d \n" , cant_alumnos);
    printf ("\n");

    //printf("---------------------------------------------------\n");

    matrixC = CrearMatriz(cant_examenes,cant_examenes);             // Matriz de conflicto inicializada
    matrixC = FillMatriz(matrixC, stu, cant_examenes);                     // Matriz de conflicto completa

    matrixAE = AsignarEA(cant_alumnos, cant_examenes, stu);  // Matriz Estudiantes x Alumnos, almacena que examen da que alumno 
    //printf("---------------------------------------------------\n");
    
    matrizSol = Greedy(matrixC, cant_examenes, &tsm); 
    printf("GREEDY TIMESLOTS: %d \n", tsm);

    //calidad = EvaluarCalidad (matrixAE, matrizSol, cant_alumnos, cant_examenes, tsm);
    //printf("CALIDAD GREEDY: %f \n", calidad);
    matrixSA = SimulatedAnnealing(matrizSol, matrixAE, matrixC, 0.8, cant_alumnos, cant_examenes, tsm, 3);

    return(0);
}