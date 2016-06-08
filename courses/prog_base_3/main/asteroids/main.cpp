
#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include "Animation.h"
#include "Entity.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include "powerup.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
using namespace sf;


  bool isCollide(Entity *a,Entity *b)      //CHECK COLLISION BETWEEN TWO CIRCLES
    {
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}




int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(W, H), "Asteroids!");
    app.setFramerateLimit(60);

    Texture Spaceship,
            Background,
            RockExplosion,
            Rock,
            FireBlue,
            FireRed,
            RockSmall,
            ShipExplosion,
            BulletPowerup;
    ///////LOADING TEXTURES FROM FILES//////
    Spaceship.loadFromFile("images/spaceship.png");
    Background.loadFromFile("images/background.jpg");
    RockExplosion.loadFromFile("images/explosions/type_C.png");
    Rock.loadFromFile("images/rock.png");
    FireBlue.loadFromFile("images/fire_blue.png");
    RockSmall.loadFromFile("images/rock_small.png");
    ShipExplosion.loadFromFile("images/explosions/type_B.png");
    BulletPowerup.loadFromFile("images/fire_red.png");

    Spaceship.setSmooth(true);
    Background.setSmooth(true);

    Sprite background(Background);

    Animation sExplosion(RockExplosion, 0,0,256,256, 48, 0.5);
    Animation sRock(Rock, 0,0,64,64, 16, 0.2);
    Animation sRock_small(RockSmall, 0,0,64,64, 16, 0.2);
    Animation sBullet(FireBlue, 0,0,32,64, 16, 0.8);
    Animation sPlayer(Spaceship, 40,0,40,40, 1, 0);
    Animation sPlayer_go(Spaceship, 40,40,40,40, 1, 0);
    Animation sExplosion_ship(ShipExplosion, 0,0,192,192, 64, 0.5);
    Animation sBulletPowerup(BulletPowerup, 0,0,32,64, 16, 0.8);


    std::list<Entity*> entities;

    for(int i=0;i<10;i++)
    {
      asteroid *aster = new asteroid();
      aster->settings(sRock, rand()%W, rand()%H, rand()%260, 25);
      entities.push_back(aster);
    }


    player *p = new player();
    p->settings(sPlayer,H/2,W/2,0,20);
    entities.push_back(p);

    Font font;
	font.loadFromFile("font.ttf");
	Text text("", font, 20);
	text.setColor(Color::Blue);
	text.setStyle(Text::Bold);
    Text time("", font, 20);
    time.setStyle(Text::Bold);
    Clock gameClock;
    gameClock.restart();
    int gameTime = 0;
    std::stringstream gameTimeString;
    /////main loop/////
    while (app.isOpen())
    {

        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::KeyReleased)
             if (event.key.code == Keyboard::Space)
              {
                  if(p->getPowerUpStatus()== 0){
                        bullet *b0 = new bullet();
                        b0->settings(sBullet,p->x,p->y,p->angle,10);
                        entities.push_back(b0);
                  }
                  else if(p->getPowerUpStatus()== 1){
                        bullet *b1 = new bullet();
                        b1->settings(sBullet,p->x,p->y,p->angle - 10,10);
                        entities.push_back(b1);
                        bullet *b2 = new bullet();
                        b2->settings(sBullet,p->x,p->y,p->angle + 10,10);
                        entities.push_back(b2);
                  }
                   else if(p->getPowerUpStatus()== 2){
                        bullet *b3 = new bullet();
                        b3->settings(sBullet,p->x,p->y,p->angle - 15,10);
                        entities.push_back(b3);
                        bullet *b4 = new bullet();
                        b4->settings(sBullet,p->x,p->y,p->angle + 15,10);
                        entities.push_back(b4);
                        bullet *b5 = new bullet();
                        b5->settings(sBullet,p->x,p->y,p->angle ,10);
                        entities.push_back(b5);
                   } else{
                        bullet *b6 = new bullet();
                        b6->settings(sBullet,p->x,p->y,p->angle,10);
                        entities.push_back(b6);
                   }
              }
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=p->turnSpeed;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=p->turnSpeed; // CREATE FIELD TURN SPEED
    if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true; //TO DO: ADD POWERUPS THAT GIVE U BIGGER INERTION AND turn SPEED
    else p->thrust=false;


    for(auto a:entities)  // CHECKING THE COLLISION BETWEEN ASTEROIDS AND BULLETS, PLAYER AND ASTEROIDS, PLAYER AND POWERUPS
     for(auto b:entities)
    {
      if (a->name=="asteroid" && b->name=="bullet")
       if ( isCollide(a,b) )
           {
            a->life=false;
            b->life=false;

            Entity *e = new Entity();
            e->settings(sExplosion,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            if(rand()%100 > 95){
            powerup *pow = new powerup();
            pow->settings(sBulletPowerup,a->x,a->y, rand()%360, 15);
            pow->name = "powerupBull";
            entities.push_back(pow);
            }else{
                if(rand()%100 > 95){
                powerup *pow = new powerup();
                pow->settings(sBulletPowerup,a->x,a->y, rand()%360, 15);
                pow->anim.sprite.setColor(Color::Cyan);
                pow->name = "powerupStats";
                entities.push_back(pow);
                }
            }

            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             Entity *e = new asteroid();
             e->settings(sRock_small,a->x,a->y,rand()%360,15);
             entities.push_back(e);
            }

           }

      if (a->name=="player" && b->name=="asteroid")
       if ( isCollide(a,b) )
           {
            gameClock.restart();
            reinterpret_cast<player*>(a)->reset();
            b->life=false;
            //p->life=false;
            Entity *e = new Entity();
            e->settings(sExplosion_ship,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            p->settings(sPlayer,W/2,H/2,rand()%360,20);
            p->dx=0; p->dy=0;
           }

       if (a->name=="player" && b->name=="powerupBull")
       if ( isCollide(a,b) )
           {
            b->life=false;
            reinterpret_cast<player*>(a)->addBullets();
            //p->life=false;
           }
       if (a->name=="player" && b->name=="powerupStats")
       if ( isCollide(a,b) )
           {
            b->life=false;
            reinterpret_cast<player*>(a)->addStats();
            //p->life=false;
           }
    }


    if (p->thrust)  p->anim = sPlayer_go;                    //FIRE WHILE THURSTING
    else   p->anim = sPlayer;

    for(auto e:entities)
     if (e->name=="explosion")                               //EXPLOSIONS TO END
      if (e->anim.isEnd()) e->life=0;

    if (rand()%100 < p->asteroidFrequency){                     // RANDOMLY CREATE ASTEROIDS; 1 - IS AN ASTEROIDS FREQUENCY
       asteroid *a = new asteroid();
       a->settings(sRock, 0,rand()%H, rand()%360, 25);
       entities.push_back(a);
     }

    for(auto i=entities.begin();i!=entities.end();)          //UPDATE ALL ETNITIES IN THE GAME
    {
      Entity *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entities.erase(i); delete e;}
      else i++;
    }

////

    gameTime = (int)gameClock.getElapsedTime().asSeconds();
    gameTimeString.str(" ");
    gameTimeString << gameTime;
   // cout<<gameTimeString.str());
    text.setString("Time:");
    time.setString(gameTimeString.str());
    time.setPosition(130, 40);
    text.setPosition(40, 40);
    app.draw(background);
////

   for(auto i:entities)
     i->draw(app);

    app.draw(text);
    app.draw(time);
    app.display();
    }

    return 0;
}
