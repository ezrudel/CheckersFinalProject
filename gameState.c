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

struct pos* pos(int x, int y) { // returns a pointer to a pos struct with the fields x and y
	struct pos* p = malloc(sizeof(struct pos));
	p->x = x;
	p->y = y;
	return p;
}

int getType(struct pos* p) { // returns type of square at position p
	return board[p->x][p->y];
}

int isMyPiece(struct pos* p, int side) { // returns 1 if p contains a piece belonging to side, returns 0 otherwise
	int type = getType(p);
	if (type == side || type == 2+side) {
		return 1;
	}
	return 0;
}

struct pos** getMoves(struct pos* p) { // returns an array of pointers to positions to which the piece at p can move, terminated by a null pointer, returns null if p is not a piece
	if (getType(p) < 1) {
		return NULL;
	}
	int i = 0;
	struct pos** moves = malloc(5 * sizeof(struct pos*));;
	if ((getType(p) == COMP || isKing(p)) && (p->y < SIZE-1)) {
		if ((board[(p->x)-1][(p->y)+1] == BLACK) && (p->x > 0)) {
			struct pos* q = pos((p->x)-1, (p->y)+1);
			moves[i] = q;
			i++;
		}	
		if ((board[(p->x)+1][(p->y)+1] == BLACK) && (p->x < SIZE-1)) {
			struct pos* q = pos((p->x)+1, (p->y)+1);
			moves[i] = q;
			i++;
		}
	}
	if ((getType(p) == USER || isKing(p)) && (p->y > 0)) {	
		if ((board[(p->x)-1][(p->y)-1] == BLACK) && (p->x > 0)) {
			struct pos* q = pos((p->x)-1, (p->y)-1);
			moves[i] = q;
			i++;
		}	
		if ((board[(p->x)+1][(p->y)-1] == BLACK) && (p->x < SIZE-1)) {
			struct pos* q = pos((p->x)+1, (p->y)-1);
			moves[i] = q;
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

int isKing(struct pos* p) { // returns a positive value if position p contains a king, 0 otherwise
	return ((getType(p) == USER_K) || (getType(p) == COMP_K));
}

void printBoard() { // prints out numeric values of the board (for testing)
	printf("\n\n");
	for (int y = 0; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			printf("\t%d", board[x][y]);
			//printf(" (%d, %d)", x, y);
		}
		printf("\n\n");
	}
}

int containsPos(struct pos** squares, struct pos* square) { // returns 1 if squares contains a pos identical to square, 0 if not
	int i = 0;
	struct pos* current = squares[i];
	while (current != NULL) {
		if ((current->x == square->x) && (current->y == square->y)) {
			return 1;
		}
		i++;
		current = squares[i];
	}
	return 0;
}

int move(struct pos* from, struct pos* to) { // moves the piece at pos from to pos to. returns 1 if successful, 0 if to is not a valid destination, and -1 if there are no valid destinations
	struct pos** moves = getMoves(from);
	if (moves == NULL) {
		fprintf(stderr, "error: no piece at %d,%d", from->x, from->y);
		return -1;
	}
	if (moves[0] == NULL) {
		return -1;
	}
	if (!containsPos(getMoves(from), to)) {
		return 0;
	}
	board[to->x][to->y] = getType(from);
	board[from->x][from->y] = BLACK;
	return 1;
}

int side(struct pos* p) { // returns the side that p is on, or 0/-1 if p is not a piece
	int type = getType(p);
	if (type > 2) {
		type -= 2;
	}
	return type;
}

int opp(int side) { // returns the opposite side of side
	if (side == COMP) {
		return USER;
	} else if (side == USER) {
		return COMP;
	} else {
		return side;
	}
}

struct pos** getTakes(struct pos* p) { // returns an array of pointers to pieces that p can take, terminated by a null pointer, returns null if p is not a piece
	if (getType(p) < 1) {
		return NULL;
	}
	int i = 0;
	int mySide = side(p);
	struct pos** moves = malloc(5 * sizeof(struct pos*));;
	if ((mySide == COMP || isKing(p)) && (p->y < SIZE-1)) {
		if (side(pos(p->x-1, p->y+1) == opp(mySide)) && (p->x > 0)) {
			struct pos* q = pos((p->x)-1, (p->y)+1);
			moves[i] = q;
			i++;
		}	
		if ((board[(p->x)+1][(p->y)+1] == BLACK) && (p->x < SIZE-1)) {
			struct pos* q = pos((p->x)+1, (p->y)+1);
			moves[i] = q;
			i++;
		}
	}
	if ((getType(p) == USER || isKing(p)) && (p->y > 0)) {	
		if ((board[(p->x)-1][(p->y)-1] == BLACK) && (p->x > 0)) {
			struct pos* q = pos((p->x)-1, (p->y)-1);
			moves[i] = q;
			i++;
		}	
		if ((board[(p->x)+1][(p->y)-1] == BLACK) && (p->x < SIZE-1)) {
			struct pos* q = pos((p->x)+1, (p->y)-1);
			moves[i] = q;
			i++;
		}
	}
	moves[i] = NULL;
	return moves;
}
