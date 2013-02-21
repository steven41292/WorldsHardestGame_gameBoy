//Steven Wojcio
//A3
//Brandon "LOL" Whitehead

#ifndef GBALIB_H
#define GBALIB_H

#include <stdlib.h>
#include "win1.h"
#include "win2.h"
#include "difficultySelect.h"
#include "deathFace.h"
#include "hardestGamePic.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;


#define REG_DISPCNT *(u16 *) 0x4000000

#define MAXCOL 240		// dimension constants
#define MAXROW 160



#define RGB(r, g, b) ((r)|((g)<<5)|((b)<<10))	//makes u16 value for color given RGB values
#define GC(r,c) videoBuffer[((r*240)+c)]	//in case I need to get the color of a pixel

#define LIGHT_BLUE RGB(24,24,29)	//color options
#define LIGHTER_BLUE RGB(29,29,31)
#define BLUE RGB(0,0,24)
#define LIGHT_GREEN RGB(26,31,26)
#define GREEN RGB(0,10,0)
#define RED RGB(31,0,0)
#define YELLOW RGB(30,30,23)
#define GREY RGB(26,26,26)
#define BLACK RGB(0,0,0)

#define SCANLINECOUNTER *(u16 *)0x4000006	//for waitForVblank function


#define NUMOBJS2 6
#define NUMOBJS3 21

/* Prototypes */
void setPixel(int r, int c, u16 color);	
void drawRect(int r, int c, int width, int height, u16 color);
void stall(int x);
void drawCirc(int r, int c, int rad, u16 color);
void fillCirc(int r, int c, int rad, u16 color);
void startScreen();
int playLevel1();
int playLevel2();
int playLevel3();
void waitForVblank();
//int deathCounter();
void reset();
void drawNum(int num,int r, int c);
void drawNum(int num,int r, int c);
void drawImage3(int,int,int,int,const u16*);
void winner(int);
void gameLogic(int);
int difficultyOfPlay;	//global var to set difficulty level
int deaths;

extern u16 *videoBuffer;	//for drawing

typedef struct Circs{		
		int r;
		int c;
		int dr;
		int dc;
		int leftlimC;
		int rightlimC;
		int toplimR;
		int botlimR;
		} CIRCLES;		//structure to hold ememy circles

typedef struct USER_SQUARE{
		int r;
		int c;
		} USR;			//structure for the user's square
typedef struct DMA{
		const volatile void *src;
		const volatile void *dst;
		u32 cnt;
		}DMAREC; 
		

/* Buttons */

#define BUTTON_A      (1<<0)
#define BUTTON_B      (1<<1)
#define BUTTON_SELECT (1<<2)
#define BUTTON_START  (1<<3)
#define BUTTON_RIGHT  (1<<4)
#define BUTTON_LEFT   (1<<5)
#define BUTTON_UP     (1<<6)
#define BUTTON_DOWN   (1<<7)
#define BUTTON_R      (1<<8)
#define BUTTON_L      (1<<9)

#define BUTTONS (*( unsigned int *)0x04000130)	//value of button being pressed
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)	//returns a zero if given button isn't pressed

/*Dma Stuff*/

#define DMA ((volatile DMAREC *)0x040000B0)

/*channel 0*/
#define REG_DMA0SAD         *(u32*)0x40000B0  // source address
#define REG_DMA0DAD         *(u32*)0x40000B4  // destination address
#define REG_DMA0CNT         *(u32*)0x40000B8  // control register

/* DMA channel 1 register definitions */

#define REG_DMA1SAD         *(u32*)0x40000BC  // source address
#define REG_DMA1DAD         *(u32*)0x40000C0  // destination address
#define REG_DMA1CNT         *(u32*)0x40000C4  // control register

/* DMA channel 2 register definitions */

#define REG_DMA2SAD         *(u32*)0x40000C8  // source address
#define REG_DMA2DAD         *(u32*)0x40000CC  // destination address
#define REG_DMA2CNT         *(u32*)0x40000D0  // control register

/* DMA channel 3 register definitions */

#define REG_DMA3SAD         *(u32*)0x40000D4  // source address
#define REG_DMA3DAD         *(u32*)0x40000D8  // destination address
#define REG_DMA3CNT         *(u32*)0x40000DC  // control register

/* Defines */

#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

#endif
