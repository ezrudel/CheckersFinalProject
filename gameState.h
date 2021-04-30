#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <stdio.h>
#include <stdlib.h>

#define SIZE 8 // dimensions of board
#define RED -1 // red square (we're only playing on black squares)
#define BLACK 0 // black square
#define COMP 1 // computer's piece or general reference to computer
#define USER 2 // user's piece or general reference to user
#define COMP_K 3 // computer's king
#define USER_K 4 // user's king

void initBoard();
void startGame();
void printBoard();
struct pos p(int x, int y);
int getType(struct pos p);
int isMyPiece(struct pos p, int side);
struct pos* getMoves(struct pos p);
void king();
int isKing(struct pos p);

struct pos {
	int x, y;
};

#endif
