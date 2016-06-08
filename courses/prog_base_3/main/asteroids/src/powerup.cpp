#include "powerup.h"

powerup::powerup()
{
    dx=rand()%4-2;
    dy=rand()%4-2;
    speed = 1;

}

void  powerup::update()
  {
   dx=cos(angle*DEGTORAD)*speed;
   dy=sin(angle*DEGTORAD)*speed;
   angle+=rand()%6-2.5;

   x+=dx;
   y+=dy;

   if (x>W) x=0;
   if (x<0) x=W;
   if (y>H) y=0;
   if (y<0) y=H;
  }
