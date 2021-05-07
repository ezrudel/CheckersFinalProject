//This file keeps track of the state of the game.

#include "gameState.h"

int board[SIZE][SIZE];

void initBoard() { // initializes board with empty black & red squares
	for (int x= 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			if (((x+y) % 2) == 0) {
				board[x][y] = BLACK;
			} else {
				board[x][y] = RED;
			}
		}
	}
}

void startGame() { // initializes game with pieces in starting positions
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y] == BLACK) {
				board[x][y] = COMP;
			}
		}
	}
	for (int y = SIZE-3; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y] == BLACK) {
				board[x][y] = USER;
			}
		}
	}
}

struct pos pos(int x, int y) { // returns a pos struct with the fields x and y
	struct pos p;
	p.x = x;
	p.y = y;
	return p;
}

int getType(struct pos p) { // returns type of square at position p
	return board[p.x][p.y];
}

int isMyPiece(struct pos p, int side) { // returns 1 if p contains a piece belonging to side, returns 0 otherwise
	if (board[p.x][p.y] == side || board[p.x][p.y] == 2+side) {
		return 1;
	}
	return 0;
}

struct pos** getMoves(struct pos p) { // returns an array of pointers to positions to which the piece at p can move
	if (getType(p) < 1) {
		fprintf(stderr, "Error: not a piece");
		exit(1);
	}
	int i = 0;
	struct pos** moves = malloc(5 * sizeof(struct pos*));;
	if (getType(p) == COMP || isKing(p)) {
		if (board[(p.x)-1][(p.y)+1] == BLACK) {
			struct pos q = pos((p.x)-1, (p.y)+1);
			moves[i] = &q;
			i++;
		}	
		if (board[(p.x)+1][(p.y)+1] == BLACK) {
			struct pos q = pos((p.x)+1, (p.y)+1);
			moves[i] = &q;
			i++;
		}
	}
	if (getType(p) == USER || isKing(p)) {	
		if (board[(p.x)-1][(p.y)-1] == BLACK) {
			struct pos q = pos((p.x)-1, (p.y)-1);
			moves[i] = &q;
			i++;
		}	
		if (board[(p.x)+1][(p.y)-1] == BLACK) {
			struct pos q = pos((p.x)+1, (p.y)-1);
			moves[i] = &q;
			i++;
		}
	}
	moves[i] = NULL;
	return moves;
}

void king() { // checks the whole board for pieces that are on their opponents starting line and kings them
	for (int x = 0; x < SIZE; x++) {
		if (board[x][0] == USER) {
			board[x][0] = USER_K;
		}
	}
	for (int x = 0; x < SIZE; x++) {
		if (board[x][SIZE] == COMP) {
			board[x][SIZE] = COMP_K;
		}
	}
}

int isKing(struct pos p) {
	return ((getType(p) == USER_K) || (getType(p) == COMP_K));
}

void printBoard() { // prints out numeric values of the board (for testing)
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			printf("\t%d", board[x][y]);
		}
		printf("\n\n");
	}
}

