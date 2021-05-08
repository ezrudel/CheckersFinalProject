//This file maintains the UI for the game


#include "gameInterface.h"

void printUIBoard(){
	for(int x = 0; x < SIZE; x++){
		for(int y = 0; y < 0; y++){
			if(board[x][y] == BLACK){
				printf("E \t");
			}
			if(board[x][y] == RED){
				printf("\t");
			}
			if(board[x][y] == COMP){
				printf("CPU \t");
			}
			if(board[x][y] == USER){
				printf("USER \t");
			}
			if(board[x][y] == COMP_K){
				printf("CPU_K \t");
			}
			if(board[x][y] == USER_K){
				printf("USER_K \t");
			}
		}
		printf("\n");
	}
}
