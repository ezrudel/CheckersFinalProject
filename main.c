
#include "gameState.h"

int main() { 
	initBoard();
	startGame();
	printBoard();
	printf("%d\n", move(pos(0, 2), pos(1, 3)));
	printBoard();

	
	return 0;

}
