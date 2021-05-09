//This file keeps track of the state of the game.

#include "gameState.h"

int board[SIZE][SIZE];
int upieces;
int cpieces;

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
	upieces = 0;
	cpieces = 0;
}

void startGame() { // initializes game with pieces in starting positions
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y] == BLACK) {
				board[x][y] = COMP;
				cpieces++;
			}
		}
	}
	for (int y = SIZE-3; y < SIZE; y++) {
		for (int x = 0; x < SIZE; x++) {
			if (board[x][y] == BLACK) {
				board[x][y] = USER;
				upieces++;
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

void king() { // checks the whole board for pieces that are on their opponents starting line and kings them
	for (int x = 0; x < SIZE; x++) {
		if (board[x][0] == USER) {
			board[x][0] = USER_K;
		}
	}
	for (int x = 0; x < SIZE; x++) {
		if (board[x][SIZE-1] == COMP) {
			board[x][SIZE-1] = COMP_K;
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

int canMove(struct pos* p, int x, int y) { // determines whether the piece at p can move in the given direction <x,y> (x and y will be 1 or -1)
	struct pos* to = pos(p->x+x, p->y+y);
	return inBounds(to) && (getType(to) == BLACK);
}

struct pos** getMoves(struct pos* p) { // returns an array of pointers to places p can move, terminated by a null pointer, returns null if p is not a piece
	if (getType(p) < 1) {
		return NULL;
	}
	int i = 0;
	struct pos** moves = malloc(5 * sizeof(struct pos*));;
	if ((getType(p) == COMP) || isKing(p)) {
		if (canMove(p, -1, 1)) {
			struct pos* q = pos((p->x)-1, (p->y)+1);
			moves[i] = q;
			i++;
		}	
		if (canMove(p, 1, 1)) {
			struct pos* q = pos((p->x)+1, (p->y)+1);
			moves[i] = q;
			i++;
		}
	}
	if ((getType(p) == USER) || isKing(p)) {	
		if (canMove(p, -1, -1)) {
			struct pos* q = pos((p->x)-1, (p->y)-1);
			moves[i] = q;
			i++;
		}	
		if (canMove(p, 1, -1)) {
			struct pos* q = pos((p->x)+1, (p->y)-1);
			moves[i] = q;
			i++;
		}
	}
	moves[i] = NULL;
	return moves;
}

int move(struct pos* from, struct pos* to) { // moves the piece at pos from to pos to. returns 1 if successful, 0 if to is not a valid destination, and -1 if there are no valid destinations
	struct pos** moves = getMoves(from);
	struct pos** takes = getTakes(from);
	if (moves == NULL) {
		fprintf(stderr, "error: no piece at %d,%d", from->x, from->y);
		return -1;
	}
	if ((moves[0] == NULL) && (takes[0] == NULL)) {
		return -1;
	}
	if (containsPos(moves, to)) {
		board[to->x][to->y] = getType(from);
		board[from->x][from->y] = BLACK;
		return 1;
	}
	if (containsPos(takes, to)) {
		if (side(from) == COMP) {
			upieces--;
		} else {
			cpieces--;
		}
		board[to->x][to->y] = getType(from);
		board[from->x][from->y] = BLACK;
		int xdir = to->x - from->x;
		xdir = xdir / abs(xdir);
		int ydir = to->y - from->y;
		ydir = ydir / abs(ydir);
		board[from->x+xdir][from->y+ydir] = BLACK;
		return 1;
	}
	return 0;
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

int inBounds(struct pos* p) { // determines whether p is within the board
	return (p->x >= 0) && (p->x < SIZE) && (p->y >= 0) && (p->y < SIZE);
}

int canTake(struct pos* p, int x, int y) { // determines whether the piece at p can take another piece in the given direction <x,y> (x and y will be 1 or -1)
	struct pos* one = pos(p->x+x, p->y+y);
	struct pos* two = pos(p->x+(x*2), p->y+(y*2));
	return inBounds(two) && (getType(two) == BLACK) && (side(one) == opp(side(p)));
}

struct pos** getTakes(struct pos* p) { // returns an array of pointers to pieces that p can take, terminated by a null pointer, returns null if p is not a piece
	if (getType(p) < 1) {
		return NULL;
	}
	int i = 0;
	struct pos** takes = malloc(5 * sizeof(struct pos*));;
	if ((getType(p) == COMP) || isKing(p)) {
		if (canTake(p, -1, 1)) {
			struct pos* q = pos((p->x)-2, (p->y)+2);
			takes[i] = q;
			i++;
		}	
		if (canTake(p, 1, 1)) {
			struct pos* q = pos((p->x)+2, (p->y)+2);
			takes[i] = q;
			i++;
		}
	}
	if ((getType(p) == USER) || isKing(p)) {	
		if (canTake(p, -1, -1)) {
			struct pos* q = pos((p->x)-2, (p->y)-2);
			takes[i] = q;
			i++;
		}	
		if (canTake(p, 1, -1)) {
			struct pos* q = pos((p->x)+2, (p->y)-2);
			takes[i] = q;
			i++;
		}
	}
	takes[i] = NULL;
	return takes;
}

void reverse(struct pos* from, struct pos* to) { // reverses the move between from and to
	int temp = getType(from);
	board[from->x][from->y] = getType(to);
	board[to->x][to->y] = temp;
	int xdif = to->x - from->x;
	int ydif = to->y - from->y;
	if (abs(xdif) == 2) {
		board[from->x+(xdif/2)][from->y+(ydif/2)] = opp(side(from));
	}
}

int winner() { // returns the value of the winner, 0 if no one has one
	if (upieces == 0) {
		return COMP;
	}
	if (cpieces == 0) {
		return USER;
	}
	return 0;
}
