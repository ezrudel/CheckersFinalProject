#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H


void printUIBoard(); // prints board with text UI
void printBorder(); // prints one line of border
void userTurn(); // prompts user to take turn
struct pos* getFrom(); // prompts user for a from piece
struct pos* getTo(); // prompts user for a to piece

#endif
