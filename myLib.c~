#include "myLib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int r, int c, unsigned short color)
{
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{
		for(int c=0; c<width; c++)
		{
			setPixel(row+r, col+c, color);
		}
	}
}

void delay(int n)
{
	volatile int x = 0;
	for(int i=0; i<n*10000; i++)
	{
		x++;
	}
}

//use DMA to draw an image

void drawImage3(int r, int c, int width, int height, const u16* image)
{
    for (int i = 0; i < height; i++) 
	{
		DMA[3].src = image + i*width;
   		DMA[3].dst = videoBuffer + NUMSCREENCOLS*(r + i) + c;
    		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
	}
}

void drawBackground(const u16* image)
{

	DMA[3].src = image;
   	DMA[3].dst = videoBuffer;
    	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
	
}

void drawBackground2(volatile u16* color)
{

	DMA[3].src = color;
   	DMA[3].dst = videoBuffer;
    	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED | DMA_DESTINATION_INCREMENT;
	
}

//Write text

void drawChar(int row, int col, char ch, u16 color)
{
	for (int r=0; r<8; r++)
	{
		for (int c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r,c,6) + ch*48])
			{
				setPixel(row+r, col+c, color);
			}
		}
	}
}

void drawString(int row, int col, char*str, u16 color)
{
	while(*str)		//what is this notation?
	{
		drawChar(row, col, *str++, color);
		col+=6;
	}
}




//wait for blank
void waitForVblank()
{
	//vblank is basically a pause. you draw during that time. forced pause and you wait for code.

	while(SCANLINECOUNTER >= 160); //if you're at a line greater than 160, wait until next vblank
	while(SCANLINECOUNTER < 160); //if you're at a line less than 160, wait until vblank. 
}
