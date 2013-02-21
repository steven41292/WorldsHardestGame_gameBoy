//Steven Wojcio
//A3
//B-Rand 
//not nearly as hard as the real one..

#include "GBAlib.h"


/*This is the main function for my GBA game. It simply sets the Display control register and then calls the gameLogic function.*/
int main(void){
	REG_DISPCNT = 1027;
	gameLogic(1);
	return 0;
}

