#ifndef AI_H
#define AI_H

#include "gameState.h"

void compTurn(); // the computer takes a turn
struct move* minimax(struct move* best, int mySide, int depth); // minimax algorithm
void printMove(struct move* m); // prints a string version of m
int heur(int side, int depth); // calls minimax on the opposite side and returns the negative heuristic value of the move returned

struct move { // represents a move from from to to
	struct pos* from;
	struct pos* to;
	int value; // heuristic value
};

#endif
