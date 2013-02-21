//Steven Wojcio

#include "GBAlib.h"
/*Level 3 logic*/
int playLevel3(){
	drawRect(30,30,180,40,LIGHT_BLUE);
	drawRect(80,30,180,40,LIGHT_BLUE);
	drawRect(70,170,40,10,LIGHT_BLUE);

	drawRect(30,2,28,28,LIGHT_GREEN);
	drawRect(92,2,28,28,LIGHT_GREEN);

	CIRCLES circs[NUMOBJS3];
	CIRCLES oldcircs[NUMOBJS3];
	CIRCLES *ptr;
	USR usr[1];
	USR oldusr[1];
	

	usr->r=45;
	usr->c=15;	
	oldusr[0]=usr[0];
	int i;
	int stillOnLevel3=1;

	//DMA[3].src = &LIGHT_BLUE;
	//DMA[3].dst = videoBuffer;
	//DMA[3].cnt = 38400  | DMA_ON | DMA_SOURCE_FIXED;

	for(i=0;i<(NUMOBJS3-1);i++){
		if(i<10){
			(circs+i)->r=(((2+i)%2)*30+35);
			(circs+i)->c=(i*15+35);
			(circs+i)->dr=difficultyOfPlay;
			(circs+i)->dc=difficultyOfPlay;
			(circs+i)->toplimR=35;
			(circs+i)->botlimR=65;
			(circs+i)->leftlimC=(i*15+38);
			(circs+i)->rightlimC=(i*15+68);
		}
		else{
			(circs+i)->r=(((2+i)%2)*30+85);
			(circs+i)->c=((i-10)*15+35);
			(circs+i)->dr=difficultyOfPlay+1;
			(circs+i)->dc=1;
			(circs+i)->toplimR=85;
			(circs+i)->botlimR=115;
			(circs+i)->leftlimC=((i-10)*15+35);
			(circs+i)->rightlimC=((i-10)*15+65);
		}
		
	oldcircs[i]=circs[i];
	}

	(circs+20)->r=75;
	(circs+20)->c=175;
	(circs+20)->dr=0;
	(circs+20)->dc=2;
	(circs+20)->toplimR=0;
	(circs+20)->botlimR=180;
	(circs+20)->leftlimC=175;
	(circs+20)->rightlimC=205;
	oldcircs[20]=circs[20];
	while(stillOnLevel3==1)
	{
		if(KEY_DOWN_NOW(BUTTON_SELECT)){
			reset(1);
		}
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			(usr->r)--;
			if(usr->r<=30){ usr->r = 30;}
			if((usr->r>70)&&(usr->r<=80)&&(usr->c<170)){ usr->r = 80;}
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			usr->r++;	
			if(usr->r>=145) usr->r = 145;
			if((usr->r<80)&&(usr->r>=65)&&(usr->c<170)){
				usr->r=65;
			}
			if((usr->c<30)&&(usr->r>=53))usr->r=53;
			if(usr->r>=115) usr->r=115;
			
		}	
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			usr->c--;
			if(usr->c<=2) usr->c=2;
			if((usr->r>53)&&(usr->c<30)){
				usr->c++;
			}
			if((usr->r<80)&&(usr->r>65)&&(usr->c<170)){
				usr->c++;
			}
			if((usr->r>92)&&(usr->c==30)){
				stillOnLevel3=0;
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			usr->c++;
			if(usr->c>=220) usr->c=220;
			if((usr->r<122)&&(usr->c>205)){
				usr->c--;
			}
		}

		for(i=0; i<NUMOBJS3; i++)
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
		waitForVblank();		// Draw the object

		for(i=0; i<NUMOBJS3; i++)
		{
			// Erase the object
			fillCirc(oldcircs[i].r, oldcircs[i].c, 3, LIGHT_BLUE);
		}
		
		for(i=0; i<NUMOBJS3; i++)
		{
			// Draw the object
			
			fillCirc(circs[i].r, circs[i].c, 3, YELLOW);
			oldcircs[i] = circs[i];
		}
		if(usr->c<30){
			drawRect(oldusr->r,oldusr->c,5,5,LIGHT_GREEN);}
		else{
		drawRect(oldusr->r,oldusr->c,5,5,LIGHT_BLUE);}
		drawRect(30,30,6,29,LIGHT_BLUE);
		drawRect(30,29,1,28,LIGHT_GREEN);
		drawRect(usr->r,usr->c,5,5,RED);
		oldusr[0]=usr[0];
		stall(8);
	}
	return 0;
}
