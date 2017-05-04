#include <stdio.h>
#include "LPC17xx.H"                         /* LPC17xx definitions           */
#include "GLCD.h"
#include "CRIS_UTILS.h"

#define __FI        1                       /* Font index 16x24               */
volatile int Cannon_Pos=145;//x position of cannon
int Cannon_Vert=195;//y position of cannon
volatile int Bullet_yPos;
volatile int Bullet_xPos;                                                                         

void Draw_Rect( int x0, int y0, int width, int height)
{
	int i;
	int j;
for(i=0; i<height; i++)
{ for(j=0; j<width; j++)
	{ GLCD_PutPixel(x0+j,y0+i);
	}
  }
}


//Draw Cannon
void Draw_Cannon(int x0, int y0)
{
    GLCD_SetTextColor(Green);
    Draw_Rect(x0,y0,30,10);
    Draw_Rect(x0+10,y0-10,10,10);
	  Draw_Rect(x0+10,y0+10,10,10);
}

//Move the Cannon

void Move_Cannon_Left(void)
{
	int moveAmount=1;//specifies how many pixels the cannon moves
	Cannon_Pos -= moveAmount;
  GLCD_SetTextColor(Black);
	Draw_Rect(Cannon_Pos+30,Cannon_Vert,moveAmount,10);
	Draw_Rect(Cannon_Pos+20,Cannon_Vert-10,moveAmount,10);
	GLCD_SetTextColor(Green);
	Draw_Rect(Cannon_Pos,Cannon_Vert,moveAmount,10);
	Draw_Rect(Cannon_Pos+10,Cannon_Vert-10,moveAmount,10);
}
//This function moves the cannon right
void Move_Cannon_Right(void)
{
	int moveAmount=1;//specifies how many pixels the cannon moves
	Cannon_Pos += moveAmount;
	GLCD_SetTextColor(Black);
	Draw_Rect(Cannon_Pos-moveAmount,Cannon_Vert,moveAmount,10);
	Draw_Rect(Cannon_Pos+10-moveAmount,Cannon_Vert-10,moveAmount,10);
	GLCD_SetTextColor(Green);
	Draw_Rect(Cannon_Pos+30-moveAmount,Cannon_Vert,moveAmount,10);
	Draw_Rect(Cannon_Pos+20-moveAmount,Cannon_Vert-10,moveAmount,10);
}
//This function draws the cannon's bullet
void Draw_Bullet(void)
{
	Bullet_yPos=179;
	GLCD_SetTextColor(White);
	Bullet_xPos=Cannon_Pos;
	Draw_Rect(Cannon_Pos+10,Bullet_yPos,10,6);
	Draw_Rect(Cannon_Pos+12,Bullet_yPos-6,10,6);
}

void Move_Bullet_Up(void)
{
	Bullet_yPos--;
	GLCD_SetTextColor(White);
	Draw_Rect(Bullet_xPos+14,Bullet_yPos,2,1);
	GLCD_SetTextColor(Black);
	Draw_Rect(Bullet_xPos+14,Bullet_yPos+6,2,1);
}
