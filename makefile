solver: main.o cubeops.o
	gcc -Wall -o solver main.o cubeops.o

main.o: main.c cubeops.h
	gcc -Wall -c main.c 

cubeops.o: cubeops.c cubeops.h
	gcc -Wall -c cubeops.c