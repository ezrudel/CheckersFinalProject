FLAGS = -g -std=c99 -pedantic -Wall -Wextra
PROGRAMS = main
OBJS = main.o gameState.o gameInterface.o ai.o

all: $(PROGRAMS) 

main: main.o gameState.o gameInterface.o ai.o
	gcc $(FLAGS) -o main main.o gameState.o gameInterface.o ai.o

main.o: main.c
	gcc $(FLAGS) -c main.c

gameState.o: gameState.c
	gcc $(FLAGS) -c gameState.c

gameInterface.o: gameInterface.c
	gcc $(FLAGS) -c gameInterface.c

ai.o: ai.c
	gcc $(FLAGS) -c ai.c

clean:
	rm $(PROGRAMS) $(OBJS)


