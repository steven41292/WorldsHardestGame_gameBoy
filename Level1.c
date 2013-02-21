//Steven Wojcio

#include "GBAlib.h"
/*Level 1 logic*/
int playLevel1(){

	drawRect(10,30,180,140,LIGHT_BLUE);		//main board
	drawRect(10,2,28,28,LIGHT_GREEN);		//Start zone
	drawRect(122,210,28,28,LIGHT_GREEN);		//End zone	

	#define NUMOBJS1 8
	
	CIRCLES circs[NUMOBJS1];	//declares 8 enemies
	CIRCLES oldcircs[NUMOBJS1];
	CIRCLES *ptr;
	USR usr[1];
	USR oldusr[1];
	

	usr->r=15;			//starting position of the user
	usr->c=15;	
	oldusr[0]=usr[0];
	int i;	
	int stillOnLevel1=1;	
	int startR=15;
	int startC=45;

	//DMA[3].src = &LIGHT_BLUE;
	//DMA[3].dst = videoBuffer;
	//DMA[3].cnt = 38400  | DMA_ON | DMA_SOURCE_FIXED;

	for(i=0;i<NUMOBJS1;i++){		//create enemies 
		(circs+i)->leftlimC=35;
		(circs+i)->rightlimC=200+((difficultyOfPlay-1)*5);
		(circs+i)->toplimR=15;
		(circs+i)->botlimR=145;
		if ((i==0)||(i==7)){		//diagonals
			(circs)->r=15;
			(circs)->c=35;
			(circs)->dr=4+difficultyOfPlay;
			(circs)->dc=3+(difficultyOfPlay*2);
			(circs+7)->r=145;
			(circs+7)->c=195;
			(circs+7)->dr=-5;
			(circs+7)->dc=-5;
			
		}
		else{				//straight up and down
			if(i%2==1){
				(circs+i)->r=startR;
				(circs+i)->c=startC;
				(circs+i)->dr=5+difficultyOfPlay;
				(circs+i)->dc=0;
				startR=135;
			}
			else{
				(circs+i)->r=startR;
				(circs+i)->c=startC;
				(circs+i)->dr=-5;
				(circs+i)->dc=0;
				startR=15;
			}
			startC+=30;
		}
		

		oldcircs[i]=circs[i];
	}
	while(stillOnLevel1==1)
	{
		if(KEY_DOWN_NOW(BUTTON_SELECT)){	//call reset if select is pressed
			reset(1);
		}
		/*Button Logic*/
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			(usr->r)--;
			if(usr->r<=10) usr->r = 10;
			
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			usr->r++;	
			if(usr->r>=145) usr->r = 145;
			if((usr->c<30)&&(usr->r>33)){
				usr->r--;
			}
			
		}	
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			usr->c--;
			if(usr->c<=2) usr->c=2;
			if((usr->r>33)&&(usr->c<30)){
				usr->c++;
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			usr->c++;
			if(usr->c>=220) usr->c=220;
			if((usr->r<122)&&(usr->c>205)){
				usr->c--;
			}
			if((usr->r>=122)&&(usr->c>205)){
				stillOnLevel1=0; //winner (they have reached final green area
			}
		}
		
		// Move the object
		if (stillOnLevel1==0)continue; //skip rest of the loop

		for(i=0; i<NUMOBJS1; i++)
		{
			ptr = circs+i;

			ptr->r += ptr->dr;
			ptr->c += ptr->dc;
		
			// Check for collisions
			if(ptr->r<ptr->toplimR)
			{
				ptr->r = ptr->toplimR;
				ptr->dr = -ptr->dr;
			}
			if(ptr->r>ptr->botlimR)
			{
				ptr->r = ptr->botlimR;
				ptr->dr = -ptr->dr;
			}
			if(ptr->c < ptr->leftlimC)
			{
				ptr->c = ptr->leftlimC;
				ptr->dc = -ptr->dc;
			}
			if(ptr->c > ptr->rightlimC)
			{
				ptr->c = ptr->rightlimC;
				ptr->dc = -ptr->dc;
			}
			if (((ptr->r)-3)<((usr->r)+5)&&((ptr->r)+3)>((usr->r))){
				if (((ptr->c)+3)>(usr->c)&&((ptr->c)-3)<(usr->c+5)){
					drawImage3(30,70,100,125,deathFace);
					stall(100);
					drawRect(0,0,240,160,GREY);
					deaths++;
					drawNum(deaths,1,232);
					return 1;
				}
				
			}
		}		
		waitForVblank(); // Draw the object
		
		for(i=0; i<NUMOBJS1; i++)
		{
			// Erase the object
			fillCirc(oldcircs[i].r, oldcircs[i].c, 3, LIGHT_BLUE);
			
		}
		
		for(i=0; i<NUMOBJS1; i++)
		{
			// Draw the object
			
			fillCirc(circs[i].r, circs[i].c, 3, YELLOW);
			oldcircs[i] = circs[i];
		}
		if(usr->c<30){
			drawRect(oldusr->r,oldusr->c,5,5,LIGHT_GREEN);}
		else{
		drawRect(oldusr->r,oldusr->c,5,5,LIGHT_BLUE);}
		drawRect(10,30,6,29,LIGHT_BLUE);
		drawRect(10,29,1,28,LIGHT_GREEN);
		drawRect(usr->r,usr->c,5,5,RED);
		oldusr[0]=usr[0];
		stall(8);
		
	}
	return 0;
}
