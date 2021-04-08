//This file keeps track of the state of the game.

#include "gameState.h"

int board[SIZE][SIZE];

void initBoard() { // initializes board with empty black & red squares
	for (int x= 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			if (((x+y) % 2) == 0) {
				board[x][y] = BLACK_SQUARE;
			} else {
				board[x][y] = RED_SQUARE;
			}
		}
	}
}

void initGame() { // initializes game with pieces in starting positions
	for (int x = 0; x < 3; x++) {
		for (int y = 0; y < SIZE; y++) {
			if (board[x][y] != RED_SQUARE) {
				board[x][y] = WHITE_PIECE;
			}
		}
	}
	for (int x = SIZE-3; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			if (board[x][y] != RED_SQUARE) {
				board[x][y] = RED_PIECE;
			}
		}
	}
}

void printBoard() { // prints out numeric values of the board
	for (int x= 0; x < SIZE; x++) {
		for (int y = 0; y < SIZE; y++) {
			printf("%d", board[x][y]);
		}
		printf("\n");
	}
}

