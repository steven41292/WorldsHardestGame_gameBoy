//Steven Wojcio
//A3
//Brandon "LOL" Whitehead

#include "GBAlib.h"
//establist the videoBuffer (pointer to first pixel on display)
u16 *videoBuffer = (u16 *)0x6000000;

// A function to set pixel (r, c) to the color passed in.
void setPixel(int r, int c, u16 color)
{
	videoBuffer[((r*240)+c)]=color;
}
// A function to draw a FILLED rectangle starting at (r, c)
void drawRect(int r, int c, int width, int height, u16 color)
{
	int w;
	int h;
	for(w=0; w<width; w++){
		for(h=0; h<height; h++){
			setPixel((r+h), (c+w), color);
		}
	}
}
/*A function that takes some of the computer's time so that it cannot update the screen too quickly.*/
void stall(int x){
	volatile int i;
	for (i=0;i<(x*1000);i++){
	}
}
/*Fills a circle (of a given color) in given a row and column for the center of the circle and a radius.*/
void fillCirc(int r, int c, int rad, u16 color){
	int dist=rad*rad;	//radius squared
	if (rad==0){		//no circle
		;
	}
	else{
		for (int row=(r-rad);row<(r+rad);row++){	//for rows that matter
			for (int col=(c-rad);col<(c+rad);col++){//columns that matter
				if ((((row-r)*(row-r))+((col-c)*(col-c)))<=dist){
					setPixel(row,col,color);
				//set pixel if within distance radius from the center
				}
			}
		}
	}
}
/*Outlines a circle with given parameters. I used this in an early version of the game.*/
void drawCirc(int r, int c, int rad, u16 color){
	int dist=rad*rad;
	if (rad==0){
		;
	}
	else{
		for (int row=(r-rad);row<(r+rad);row++){
			for (int col=(c-rad);col<(c+rad);col++){
				if (((((row-r)*(row-r))+((col-c)*(col-c)))==(dist-1))||((((row-r)*(row-r))+((col-c)*(col-c)))==(dist-4))){
					setPixel(row,col,color);
				}
			}
		}
	}
}
/*Start screen for game. It should ask what difficulty level is desired and have a start button.*/
void startScreen(){
	int stillStarting=1;
	
	drawRect(125,63,20,2,BLUE);
	difficultyOfPlay=1;
	while(stillStarting){

		

		if(KEY_DOWN_NOW(BUTTON_RIGHT)){
			drawRect(125,63,20,2,BLACK);
			drawRect(125,138,50,2,BLUE);
			difficultyOfPlay=2;
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT)){
			drawRect(125,138,50,2,BLACK);
			drawRect(125,63,20,2,BLUE);
			difficultyOfPlay=1;
		}
		if(KEY_DOWN_NOW(BUTTON_A)){
			return;
		}
		if(KEY_DOWN_NOW(BUTTON_SELECT)){
			reset(1);
		}
	}
}

/*This code checks which pixel of the videoBuffer is being updated so that other code is only run during the Vblank stage.*/
void waitForVblank(){
	while(SCANLINECOUNTER>160);
	while(SCANLINECOUNTER<160);
}

/*Draws numbers 0-9 (in red) as 4x5 representations.*/
void drawDigits(int num,int r, int c){	//num has to be less than ten
	int b=RED;
	if (num==1) drawRect(r,c+3,1,5,b);
	if (num==2){
		drawRect(r,c,4,1,b);
		drawRect(r,c+3,1,3,b);
		drawRect(r+2,c,4,1,b);
		drawRect(r+2,c,1,3,b);
		drawRect(r+4,c,4,1,b);
	}
	if (num==3){
		drawRect(r,c,4,1,b);
		drawRect(r,c+3,1,5,b);
		drawRect(r+2,c+1,3,1,b);
		drawRect(r+4,c,4,1,b);
	}
	if (num==4){
		drawRect(r,c,1,3,b);
		drawRect(r,c+3,1,5,b);
		drawRect(r+2,c,4,1,b);
	}
	if (num==5){
		drawRect(r,c,4,1,b);
		drawRect(r,c,1,3,b);
		drawRect(r+2,c,4,1,b);
		drawRect(r+4,c,4,1,b);
		drawRect(r+2,c+3,1,3,b);
	}
	if (num==6){
		drawRect(r,c,4,1,b);
		drawRect(r,c,1,5,b);
		drawRect(r+2,c,4,1,b);
		drawRect(r+4,c,4,1,b);
		drawRect(r+2,c+3,1,3,b);
	}
	if (num==7){
		drawRect(r,c,4,1,b);
		drawRect(r,c+3,1,5,b);
	}
	if (num==8){
		drawRect(r,c,1,5,b);
		drawRect(r,c,4,1,b);
		drawRect(r+2,c,4,1,b);
		drawRect(r+4,c,4,1,b);
		drawRect(r,c+3,1,5,b);
	}
	if (num==9){
		drawRect(r,c,1,3,b);
		drawRect(r,c,4,1,b);
		drawRect(r+2,c,4,1,b);
		drawRect(r+4,c,4,1,b);
		drawRect(r,c+3,1,5,b);
	}
	if (num==0){
		drawRect(r,c,1,5,b);
		drawRect(r,c,4,1,b);
		drawRect(r+4,c,4,1,b);
		drawRect(r,c+3,1,5,b);
	}
}
/*Draws number (first parameter) in such a location that the row and column of the upper left pixel of the least significant digit (second two parameters) determines the location.*/
void drawNum(int num, int r, int c){
	int last=(num%10);
	int rest=num/10;
	if ((rest)==0){
		drawDigits(last,r,c);
		return;
	}
	else{
		drawNum(rest,r,c-5);
		drawDigits(last,r,c);
			
	}
	
	
}

/*This is for when a player beats the third level. It checks the difficulty level and then determines which winning screen to go to based on that.*/
void winner(int x){
	int temp=1;
		if(x==1){
			drawImage3(0,0,240,160,wind1);
			drawNum(deaths,70,125);
			while(temp){
				if (KEY_DOWN_NOW(BUTTON_A)){
					;reset(2);
				}
				if (KEY_DOWN_NOW(BUTTON_SELECT)){
					;reset(1);
				}
			}
		}
		else{
			drawImage3(0,0,240,160,wind2);
			drawNum(deaths,70,125);
			while(temp){
				if (KEY_DOWN_NOW(BUTTON_A)){
					reset(1);
				}
				if (KEY_DOWN_NOW(BUTTON_SELECT)){
					;reset(1);
				}
			}
		}
}

/*This simply recalls the game logic function.*/
void reset(int a){
	gameLogic(a);
}

/*This is the main logic of the game. It takes in an int to let it know where it is being called from. It can either jump straight to the first level on extreme difficulty or go back tohe start screen. For the levels, it has while loops that don't break until the level is either beat or the reset button is pressed.*/
void gameLogic(int a){

	deaths=0;
	if (a==1);
	else {difficultyOfPlay=2;
		goto Skip_point;
		}

	drawImage3(0,0,240,160,hardestGamePic);
	while(!KEY_DOWN_NOW(BUTTON_START));

	drawImage3(0,0,240,160,difficulty1);
	startScreen();	
		
	Skip_point:
	drawRect(0,0,MAXCOL,MAXROW,GREY);	//makes screen grey to start
	
	while(playLevel1());
	drawRect(6,0,MAXCOL,MAXROW-6,GREY);

	while(playLevel2());
	drawRect(6,0,MAXCOL,MAXROW-6,GREY);

	while(playLevel3());
	drawRect(6,0,MAXCOL,MAXROW-6,GREY);

	winner(difficultyOfPlay);
}
 /* drawimage3
 * A function that will draw an arbitrary sized image
 * onto the screen (with DMA).
 * @param r row to draw the image
 * @param c column to draw the image
 * @param width width of the image
 * @param height height of the image
 * @param image Pointer to the first element of the image. 
 */

void drawImage3(int r, int c, int width, int height, const u16* image)
{
	int index=0;
	for(r=r;r<height;r++){
		DMA[3].src = image+index;
		DMA[3].dst = videoBuffer+((r*240)+c);
		DMA[3].cnt = ((width)  | DMA_ON | DMA_SOURCE_INCREMENT);
		index+=width;
	}
} 

