BIN = flow.exe
OBJ = edge.o vertex.o vector.o input.o matrix.o queue.o graph.o maxflow.o output.o main.o
CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -ansi -g

$(BIN): $(OBJ)
		gcc $(OBJ) -o $(BIN) $(CCFLAGS)

edge.o: edge.c
		$(CC) -c edge.c $(CCFLAGS)

vertex.o: vertex.c
		$(CC) -c vertex.c $(CCFLAGS)

vector.o: vector.c
		$(CC) -c vector.c $(CCFLAGS)

input.o: input.c
		$(CC) -c input.c $(CCFLAGS)

matrix.o: matrix.c
		$(CC) -c matrix.c $(CCFLAGS)

queue.o: queue.c
		$(CC) -c queue.c $(CCFLAGS)

graph.o: graph.c
		$(CC) -c graph.c $(CCFLAGS)

maxflow.o: maxflow.c
		$(CC) -c maxflow.c $(CCFLAGS)

output.o: output.c
		$(CC) -c output.c $(CCFLAGS)

main.o: main.c
		$(CC) -c main.c $(CCFLAGS)

clear_ALL:
		del *.o
		del *.exe