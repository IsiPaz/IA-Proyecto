run: programa
		./programa

CC=gcc
CFLAGS=-lm
DEPS = lista.h
OBJ = lista.o proyecto.o 

#compila el programa principal
programa: $(OBJ)
	gcc -Wall -o programa proyecto.o lista.o $(CFLAGS)

proyecto.o: proyecto.c lista.h
	gcc -Wall -c proyecto.c $(CFLAGS)

lista.o: lista.c 
	gcc -Wall -c lista.c $(CFLAGS)

clean:
	rm -f programa *.o
