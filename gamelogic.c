// Game Logic for GBA
// Name: ISHITA CHORDIA

// Headers
#include "myLib.h"

// Function prototypes
void decreaseLife(int*);


//Move mainObj using keyboard
void moveMainObj(MOVOBJ* mainObj)
{
	if(KEY_DOWN_NOW(BUTTON_RIGHT)) 
	{
		mainObj->col++; 
	}
	if(KEY_DOWN_NOW(BUTTON_LEFT)) 
	{
		mainObj->col--; 
	}
	if(KEY_DOWN_NOW(BUTTON_UP)) 
	{
		mainObj->row--; 
	}
	if(KEY_DOWN_NOW(BUTTON_DOWN)) 
	{
		mainObj->row++; 
	}

	//keep object on screen
	if(mainObj->col < 0)
    	{
        	mainObj->col = 0;
    	}
    	if(mainObj->col > LASTSCREENCOL- mainObj->width + 1)
    	{
        	mainObj->col = LASTSCREENCOL- mainObj->width + 1;
   	}
	if(mainObj->row < 8)
    	{
        	mainObj->row = 8;
    	}
    	if(mainObj->row > LASTSCREENROW- mainObj->height + 1)
    	{
        	mainObj->row = LASTSCREENROW- mainObj->height + 1;
   	 }

}


void moveSquares(MOVOBJ* objs, int numObjs) {

 	//Horizontal movement of the squares
	for(int i=0; i< numObjs; i++)
	{
	   MOVOBJ* cur = objs + i;
	    
	    cur->col += cur->cdel;
	    
	    if(cur->col < 0)
	    {
	        cur->col = 0;
	        cur->cdel = -cur->cdel;
	    }
	    
	    if(cur->col > LASTSCREENCOL- cur->width + 1)
	    {
	        cur->col = LASTSCREENCOL- cur->width + 1;
	        cur->cdel = -cur->cdel;
	    }
	}
}	



//Collision detection
void collision(MOVOBJ* objs, MOVOBJ mainObj, int numObjs, int *lives)
{
	for(int i=0; i<numObjs; i++)
	{
		MOVOBJ* obj = objs + i;
	
		//top left of mainObj hits bottom right of obj
		if ( (obj->row <= mainObj.row) && ((obj->row + obj->height) >= mainObj.row) && (obj->col <= 			mainObj.col) && ((obj->col + obj->width) >= mainObj.col) ) 
		{
			decreaseLife(lives);
		}

		//bottom right of mainObj hits top left of obj
		if ( (obj->row <= (mainObj.row + mainObj.height)) && (obj->row >= mainObj.row) && (obj->col >= 				mainObj.col) && (obj->col <= (mainObj.col + mainObj.width)) ) 
		{
			decreaseLife(lives);
		}

		//top right of mainObj hits bottom left of obj
		if ( (obj->row <= mainObj.row) && ((obj->row + obj->height) >= mainObj.row) && (obj->col <= 				(mainObj.col + mainObj.width)) && (obj->col >= mainObj.col) ) 
		{
			decreaseLife(lives);
		}

		//bottom left of mainObj hits top right of obj
		if ( (obj->row <= (mainObj.row + mainObj.height)) && (obj->row >= mainObj.row) && ((obj->col + 				obj->width) <= (mainObj.col + mainObj.width)) && ((obj->col + obj->width) >= mainObj.col) ) 
		{
			decreaseLife(lives);
		}
    	}
}


void decreaseLife(int *numLives)
{
	(*numLives)--;	
	initialize();
}

//Detect if Peach catches luigi and mario
bool collision2(MOVOBJ* objs, MOVOBJ mainObj)
{
	
		//top left of mainObj hits bottom right of obj
		if ( (objs->row <= mainObj.row) && ((objs->row + objs->height) >= mainObj.row) && (objs->col <= 			mainObj.col) && ((objs->col + objs->width) >= mainObj.col) ) 
		{
			return 1;
		}

		//bottom right of mainObj hits top left of obj
		if ( (objs->row <= (mainObj.row + mainObj.height)) && (objs->row >= mainObj.row) && (objs->col >= 				mainObj.col) && (objs->col <= (mainObj.col + mainObj.width)) ) 
		{
			return 1;
		}

		//top right of mainObj hits bottom left of obj
		if ( (objs->row <= mainObj.row) && ((objs->row + objs->height) >= mainObj.row) && (objs->col <= 				(mainObj.col + mainObj.width)) && (objs->col >= mainObj.col) ) 
		{
			return 1;
		}

		//bottom left of mainObj hits top right of obj
		if ( (objs->row <= (mainObj.row + mainObj.height)) && (objs->row >= mainObj.row) && ((objs->col + 				objs->width) <= (mainObj.col + mainObj.width)) && ((objs->col + objs->width) >= mainObj.col) ) 
		{
			return 1;
		}
		
	
	return 0;
}


