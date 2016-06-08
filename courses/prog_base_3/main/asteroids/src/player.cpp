#include "player.h"

player::player()
{
   name="player";
   PowerUpStatus = 0;
   statStatus = 0;
   asteroidFrequency = 1;
   inertion = 0.99;
   maxSpeed=5;
   turnSpeed = 3;
}

void player::reset(){
    statStatus = 0;
    PowerUpStatus = 0;
    asteroidFrequency = 0.75;
    inertion = 0.99;
    maxSpeed=5;
    turnSpeed = 3;
}

void player::addStats(){
    if(PowerUpStatus < 10){
        statStatus++;
        asteroidFrequency+=0.05;
        inertion*=0.99;
        maxSpeed+=2;
        turnSpeed+=0.3;
    }


}

void player::update()
{
   if (thrust)
      { dx+=cos(angle*DEGTORAD)*0.2;
        dy+=sin(angle*DEGTORAD)*0.2; }
     else
      { dx*=inertion;           //INERTION
        dy*=inertion; }

    float speed = sqrt(dx*dx+dy*dy);
    if (speed>maxSpeed)
     { dx *= maxSpeed/speed;
       dy *= maxSpeed/speed; }

    x+=dx;
    y+=dy;

    if (x>W) x=0; if (x<0) x=W;
    if (y>H) y=0; if (y<0) y=H;
}

void player::addBullets(){
    if(PowerUpStatus < 2){
        PowerUpStatus++;
    }
}

int player::getPowerUpStatus(){
    return PowerUpStatus;
}
