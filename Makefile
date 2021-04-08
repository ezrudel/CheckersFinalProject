$FLAGS = -g -std=c99 -pedantic -Wall -Wextra
$PROGRAMS = main
$OBJS = main.o gamestate.o

All: $(PROGRAMS)

main: main.o gamestate.o
	gcc $(FLAGS) -o main main.o gamestate.o

main.o: main.c
	gcc $(FLAGS) -c main.c

gamestate.o: gamestate.c
	gcc $(FLAGS) -c gamestate.c

clean:
	rm $(PROGRAMS) $(OBJS)


