#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "gameState.h"

int main() { 
	initBoard();
	startGame();
	printBoard();
	

	//if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
	//	printf("error initalizing SDL: %s\n", SDL_GetError());
	//}
	//SDL_Window *screen = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000,1000,0);
	
	return 0;

}
