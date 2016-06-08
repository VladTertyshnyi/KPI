#include "bullet.h"

bullet::bullet()
{
     name="bullet";
     speed = 10;
}

void  bullet::update()
  {
   dx=cos(angle*DEGTORAD)*speed;
   dy=sin(angle*DEGTORAD)*speed;
   angle+=rand()%6-2.5;

   x+=dx;
   y+=dy;

   if (x>W || x<0 || y>H || y<0) life=0;     //DESTROING THE BULLET IF IT LEAVES THE SCREEN
  }
