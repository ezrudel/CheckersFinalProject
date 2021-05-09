//This file maintains the UI for the game

#include "gameState.h"
#include "gameInterface.h"

void printUIBoard(){ // prints the board with text UI
	printf("\n\n");
	printBorder();
	printf("|       ");
	for (char c = 'A'; c < 'A'+SIZE; c++) {
		printf("|   %c   ", c);
	}
	printf("|\n");
	printBorder();
	for(int y = 0; y < SIZE; y++){
		printf("|   %d   ", y+1);
		for(int x = 0; x < SIZE; x++){
			printf("|");
			if(getType(pos(x, y)) == BLACK){
				printf("       ");
			}
			if(getType(pos(x, y)) == RED){
				printf("       ");
			}
			if(getType(pos(x, y)) == COMP){
				printf("  CPU  ");
			}
			if(getType(pos(x, y)) == USER){
				printf(" USER  ");
			}
			if(getType(pos(x, y)) == COMP_K){
				printf(" CPU_K ");
			}
			if(getType(pos(x, y)) == USER_K){
				printf("USER_K ");
			}
		}
		printf("|\n");
		printBorder();
	}
	printf("\n\n");
}

void printBorder() { // prints one line of border
	for (int i = 0; i < SIZE+1; i++) {
		printf("+");
		for (int j = 0; j < 7; j++) {
			printf("-");
		}
	}
	printf("+\n");
}

void userTurn() { // walks the user through talking a turn
	struct pos* from = getFrom();
	getchar();
	while (from == NULL) {
		from = getFrom();
		getchar();
	}
	struct pos* to = getTo();
	getchar();
	while (to == NULL) {
		to = getTo();
		getchar();
	}
	int success = move(from, to);
	if (success == -1) {
		printf("\nThere are no valid moves available for the piece you have chosen. Please select another piece.\n");
		userTurn();
	} else if (success == 0) {
		printf("\nThat move is not valid. Please try again.\n");
		userTurn();
	} else { // success == 1
		printf("\nSuccess!\n");
	}
}

struct pos* getFrom() { // prompts the user for a from piece
	printf("\nEnter the coordinates of the piece you wish to move: ");
	char c = (char) getchar();
	if (c < 'A' || c >= 'A'+SIZE) {
		printf("Invalid x-coordinate: %c\n", c);
		return NULL;
	}
	int x = (int) (c - 'A');
	char r = (char) getchar();
	if (r < '1' || r >= '1'+SIZE) {
		printf("Invalid y-coordinate: %c\n", r);
		return NULL;
	}
	int y = (int) (r - '1');
	struct pos* from = pos(x, y);
	if (side(from) != USER) {
		printf("%c%c is not your piece! Try again.\n", c, r);
		return NULL;
	}
	printf("You have selected %c%c\n", c, r);
	return from;
}

struct pos* getTo() { // prompts the user for a to piece
	printf("\nEnter the coordinates of the space to which you would like to move it: ");	
	char c = (char) getchar();
	if (c < 'A' || c >= 'A'+SIZE) {
		printf("Invalid x-coordinate: %c\n", c);
		return NULL;
	}
	int x = (int) (c - 'A');
	char r = (char) getchar();
	if (r < '1' || r >= '1'+SIZE) {
		printf("Invalid y-coordinate: %c\n", r);
		return NULL;
	}
	int y = (int) (r - '1');
	struct pos* to = pos(x, y);
	return to;
}
