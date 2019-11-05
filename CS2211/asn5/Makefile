program: bstree.o datatype.o main.o matrix.o 
	gcc main.o matrix.o bstree.o datatype.o -o program 
bstree.o: bstree.c bstree.h
	gcc -c bstree.c
datatype.o: datatype.c datatype.h
	gcc -c datatype.c
main.o: main.c matrix.h
	gcc -c main.c
matrix.o: matrix.c matrix.h
	gcc -c matrix.c
clean:
	rm program *.o