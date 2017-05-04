#ifndef _CRIS_UTILS_H
#define _CRIS_UTILS_H

extern void Draw_Rect( int x0, int y0, int width, int height);
extern void Draw_Cannon(int x0, int y0);
extern void Move_Cannon_Left(void);
extern void Move_Cannon_Right(void);
extern void Draw_Bullet(void);
extern void Move_Bullet_Up(void);
extern volatile int Cannon_Pos;
extern int Cannon_Vert;
extern volatile int Bullet_yPos;
extern volatile int Bullet_xPos;
extern int Draw_Black_Bullet;
extern void delay(unsigned int nCount);

#endif
