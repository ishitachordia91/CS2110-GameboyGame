// Make a simple GBA state machine
// Name: ISHITA CHORDIA

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "myLib.h"
#include "peach.h"
#include "mario.h"
#include "luigi.h"
#include "evilmushroom.h"
#include "mariobg.h"

//protocols
void resetLivesStates();

//define variables for later
const int numObjs = 5;
MOVOBJ objs[5]; 
MOVOBJ peach;
MOVOBJ mario;
MOVOBJ luigi;
int delOptions [] = {2, 3, 4};
int numDels = sizeof(delOptions) / 4;
u16 bgcolor = SKYBLUE;
int lives = 5;
int savedMario = 0;
int savedLuigi = 0;

//State enum definition
enum GBAstate{
	START,
	STARTNODRAW,
	GAME,	
	END,
	ENDNODRAW
};

void initialize() 
{
	//initialize evil mushrooms
    	for(int i=0; i< numObjs; i++)
    	{
		objs[i].row = 20 + 24*i;
		if (i % 2 == 0) 
		{
			objs[i].col = 10;
		}
		else 
		{
			objs[i].col = 230;
		}		
		objs[i].width = 15;
		objs[i].height = 15;
		objs[i].cdel = delOptions[rand() % numDels];
	}


	//initialize peach
	peach.height = 20;
	peach.width = 15;
	peach.row = NUMSCREENROWS - peach.height;
	peach.col = 3;
	peach.cdel = 3;

	//initialize mario
	mario.height = 20;
	mario.width = 15;
	mario.row = 4;
	mario.col = 215;
	mario.cdel = 0;

	//initialize luigi
	luigi.height = 20;
	luigi.width = 15;
	luigi.row = 70;
	luigi.col = 112;
	luigi.cdel = 0;
}

void resetLivesStates() {
	lives = 5;
	savedMario = 0;
	savedLuigi = 0;
}

int main()
{

	enum GBAstate state = START;
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	
	
   	while(1)  
	{
		waitForVblank();        		

		//return to title screen
		if (KEY_DOWN_NOW(BUTTON_SELECT)) {			
			state = START;	
		}

		switch(state) 
		{
		
		case START:
			drawBackground(mariobg);						
			drawString(20, 20, "Super Smash: Real Life" , WHITE);	
			drawString(45, 20, "Help Peach save M & L" , WHITE);	
			drawString(70, 20, "Press Z to start." , WHITE);	
			drawString(95, 20, "Press backspace at any time to reset." , WHITE);	
			state = STARTNODRAW;
			break;
		
		case STARTNODRAW:			
			if (KEY_DOWN_NOW(BUTTON_A)) {	
				initialize();	
				resetLivesStates();	
				state = GAME;	
			}
			break;
		
		case GAME:

		       //drawing 
			drawBackground2(&bgcolor);
			if (savedMario == 0) {
				drawImage3(4, 215, 15, 20, mario_image);
			}
			if (savedLuigi == 0) {
				drawImage3(70, 112, 15, 20, luigi_image);
			}

			char message[10];
			sprintf(message, "%d", lives);
			drawString(4, 2, message, WHITE);	

			for(int i=0; i<numObjs; i++)
			{
			  MOVOBJ* cur = objs + i;
			  drawImage3(cur->row, cur->col, cur->width, cur->height, evilmushroom);
			}
		  	drawImage3(peach.row, peach.col, peach.width, peach.height, peach_image);

			//Move objs back and forth
			moveSquares(objs, numObjs);

			//Movement of main obj
			moveMainObj(&peach);

			//collision detection of peach and evil mushrooms
			collision(objs, peach, numObjs, &lives);

			//check if peach has save mario or luigi
			if (collision2(&mario, peach)) {
				savedMario = 1;
			}
			
			if (collision2(&luigi, peach)) {
				savedLuigi = 1;
			}
			
			//end game condition
			if ((savedLuigi == 1 && savedMario == 1) || (lives <= 0)) {
				state = END;
			}
						
			break;
		
		case END:
			drawBackground(mariobg);
			drawString(20, 20, "GAME OVER." , WHITE);
			if (lives <= 0) 
			{
				drawString(40, 20, "Sorry, you lost." , WHITE);	
			}	
			if (savedLuigi == 1 && savedMario == 1) 
			{
				drawString(40, 20, "You won!" , WHITE);
			}	
			drawString(60, 20, "Press backspace to restart." , WHITE);				
			state = ENDNODRAW;
			break;

		case ENDNODRAW:
			break;

		}        
	}
    
}

