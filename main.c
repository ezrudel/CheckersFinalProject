
#include "gameState.h"

int main() { 
	initBoard();
	startGame();
	printBoard();
	printf("%d\n", move(pos(2, 6), pos(3, 5)));
	printBoard();

	
	return 0;

}
