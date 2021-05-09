
#include "gameState.h"
#include "gameInterface.h"
#include "ai.h"

int main() { 
	initBoard();
	startGame();
	printUIBoard();
	while(winner() == 0) {
		userTurn();
		king();
		printUIBoard();
		compTurn();
		king();
		printUIBoard();
	}
	
	if (winner() == COMP) {
		printf("GAME OVER. YOU LOSE!");
	} else {
		printf("CONGRATULATIONS! YOU WON");
	}

	return 0;

}
