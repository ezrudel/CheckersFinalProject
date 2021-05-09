#Checkers Game
Ezra Rudel, Seamus Higgins, Emilio Sierra, Kabir Sethi

#Description:
A checkers game that allows the user to play against an AI opponent using a text-based interface and keyboard inputs. To play the game, simply compile and run main, and answer the prompts that follow. The user goes first.

#Files:
main.c - gameplay loop
gameState.h - contains all the constants and methods from the gameState.c file
gameState.c - keeps track of the state of the game using an int array, contains all the methods used for accessing values
gameInterface.h - header for gameInterface.c
gameInterface.c - methods to display board and take input from user
ai.h - header for ai.c
ai.c - controls AI opponent

#Bugs:
The AI is prone to moving one piece in a circle indefinitely to avoid risk, especially if it has a king piece. This means that games are hard to end.
Sometimes king pieces will mysteriously "unking" themselves after travelling backwards down the board for several squares.
Double-taking is not supported at the moment.
The AI slightly favors moving pieces that are located near the bottom right corner of the board.
