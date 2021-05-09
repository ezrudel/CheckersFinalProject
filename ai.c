#include "ai.h"

void compTurn() { // the computer takes a turn
	struct move* start = malloc(sizeof(struct move));
	start->from = NULL;
	start->to = NULL;
	start->value = 0;
	struct move* m = minimax(start, COMP, 0);
	if (m == NULL) {
		printf("\nError: I can't move\n");
	}
	move(m->from, m->to);
	printf("\nI moved from ");
	printMove(m);
	printf("! Your turn now.\n");
}

void printMove(struct move* m) { // prints a string version of m
	printf("%c%c to %c%c", m->from->x+'A', m->from->y+'1', m->to->x+'A', m->to->y+'1');
}

struct move* minimax(struct move* best, int mySide, int depth) { // minimax ai algorithm
	if (depth >= 3) {
		return best;
	}
	for (int x = 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			struct pos* from = pos(x, y);
			if (side(from) == COMP) {
				struct pos** moves = getMoves(from);
				int i = 0;
				struct pos* current = moves[i];
				while (current != NULL) {
					move(from, current);
					int h = heur(mySide, depth);
					if ((h > best->value)
						       || (best->from == NULL))	{
						best->from = from;
						best->to = current;
						best->value = h;
					} else if ((h == best->value)
							&& (rand()%3 == 1)) {
						best->from = from;
						best->to = current;
					}
					reverse(from, current);
					i++;
					current = moves[i];
				}
				struct pos** takes = getTakes(from);
				i = 0;
				current = takes[i];
				while (current != NULL) {
					move(from, current);
					int h = 1 + heur(mySide, depth);
					if ((h > best->value)
						       || (best->from == NULL))	{
						best->from = from;
						best->to = current;
						best->value = h;
					} else if ((h == best->value)
							&& (rand()%3 == 1)) {
						best->from = from;
						best->to = current;
					}
					reverse(from, current);
					i++;
					current = moves[i];
				}
			}
		}
	}
	return best;
}

int heur(int mySide, int depth) {
	struct move* m = malloc(sizeof(struct move));
	m->from = NULL;
	m->to = NULL;
	m->value = 0;
	struct move* n = minimax(m, opp(mySide), depth+1);
	return -1 * n->value;
}
