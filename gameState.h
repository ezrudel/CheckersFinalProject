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


void initBoard(); // initializes the board with black and red squares

void startGame(); // puts pieces in their starting positions

void printBoard(); // prints the int values of the board

struct pos* pos(int x, int y); // returns a pos struct with values x and y

int getType(struct pos* p); // returns the value of board at p

struct pos** getMoves(struct pos* p); // returns an array of pointers to places p can move (without taking), terminated by a null pointer, returns null if p is not a piece

void king(); // kings all pieces on the board that are on their opponent's starting line

int isKing(struct pos* p); // determines whether p contains a king piece

int containsPos(struct pos** squares, struct pos* square); // determines whether squares contains an identical struct pos to square

int move(struct pos* from, struct pos* to); // moves the piece at from to to. returns 1 if successful, 0 if to is not in the range of from, and -1 if there are no valid moves from from, or if from does not contain a piece

int side(struct pos* p); // returns the side that the piece at p is on. if there is no piece at p, returns the value at p

int opp(int side); // returns the opposite side of side

int inBounds(struct pos* p); // determines whether p is within the board

int canTake(struct pos* p, int x, int y); // determines whether the piece at p can take another piece in the given direction x,y (x and y will be 1 or -1)

struct pos** getTakes(struct pos* p); // returns an array of pointers to pieces that p can take, terminated by a null pointer, returns null if p is not a piece


struct pos { // represents the position on the board (x,y) -- ONLY PASS POINTERS TO THIS STRUCT, NOT THE STRUCT ITSELF
	int x, y;
};


#endif
