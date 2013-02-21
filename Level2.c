//Steven Wojcio

#include "GBAlib.h"

/*Level 2 logic*/
int playLevel2(){

	drawRect(65,30,170,30,LIGHT_BLUE);
	drawRect(55,75,10,10,LIGHT_BLUE);
	drawRect(95,145,10,10,LIGHT_BLUE);
	drawRect(65,15,15,30,LIGHT_GREEN);
	drawRect(65,200,15,30,LIGHT_GREEN);

	CIRCLES circs[NUMOBJS2];
	CIRCLES oldcircs[NUMOBJS2];
	CIRCLES *ptr;
	USR usr[1];
	USR oldusr[1];
	

	usr->r=75;
	usr->c=20;	
	oldusr[0]=usr[0];
	int i;
	int stillOnLevel2=1;
	for(i=0;i<NUMOBJS2;i++){
		(circs+i)->r=(((3+i)%3)*9+70);
		(circs+i)->c=(((2+i)%2)*70+55);
		(circs+i)->dr=0;
		(circs+i)->dc=difficultyOfPlay;
		(circs+i)->toplimR=0;
		(circs+i)->botlimR=160;
		(circs+i)->leftlimC=(((2+i)%2)*70+50);
		(circs+i)->rightlimC=(((2+i)%2)*70+126);
		oldcircs[i]=circs[i];
	}

	while(stillOnLevel2==1)
	{
		if(KEY_DOWN_NOW(BUTTON_SELECT)){
			reset(1);
		}
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			(usr->r)--;
			if((usr->c>=75)&&(usr->c<=80)){if(usr->r<55){usr->r++;}}
			else if(usr->r<65){ usr->r++;}
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			usr->r++;
			if((usr->c>=145)&&(usr->c<=155)){if(usr->r>100){usr->r--;}}	
			else if(usr->r>=91)usr->r--;
	
			
		}	
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			usr->c--;
			if((usr->r>90)&&(usr->c<145)){
				usr->c++;
			}
			if((usr->r<65)&&(usr->c<75)){
				usr->c++;
			}
			if(usr->c<15)usr->c++;
			
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			usr->c++;
			if((usr->r>90)&&(usr->c>150)){
				usr->c--;
			}
			if((usr->r<65)&&(usr->c>80)){
				usr->c--;
			}
			if(usr->c>195)//win
				stillOnLevel2=0;
			;
		}

		for(i=0; i<NUMOBJS2; i++)
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

		
		for(i=0; i<NUMOBJS2; i++)
		{
			// Erase the object
			fillCirc(oldcircs[i].r, oldcircs[i].c, 3, LIGHT_BLUE);
		}
		
		for(i=0; i<NUMOBJS2; i++)
		{
			// Draw the object
			
			fillCirc(circs[i].r, circs[i].c, 3, YELLOW);
			oldcircs[i] = circs[i];
		}
		if(usr->c<30){
			drawRect(oldusr->r,oldusr->c,5,5,LIGHT_GREEN);}
		else{
		drawRect(oldusr->r,oldusr->c,5,5,LIGHT_BLUE);}
		drawRect(65,30,6,30,LIGHT_BLUE);
		drawRect(65,29,1,30,LIGHT_GREEN);
		drawRect(usr->r,usr->c,5,5,RED);
		oldusr[0]=usr[0];
		stall(8);
	}
	return 0;
}
