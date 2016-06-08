#include "Game.h"
using namespace sf;

bool isCollide(Entity *a,Entity *b)      //CHECK COLLISION BETWEEN TWO CIRCLES
{
  return (b->x - a->x)*(b->x - a->x)+
         (b->y - a->y)*(b->y - a->y)<
         (a->R + b->R)*(a->R + b->R);
}

Game::Game()
{
   SetAnimations();
   InitialAster();
   CreatePlayer();

}


void Game::CheckColisions(){
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

            if(rand()%10 > 8){
            powerup *pow = new powerup();
            pow->settings(sBulletPowerup,a->x,a->y, p->angle, 10);
            entities.push_back(pow);
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
            b->life=false;
            //p->life=false;
            Entity *e = new Entity();
            e->settings(sExplosion_ship,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            p->settings(sPlayer,W/2,H/2,0,20);
            p->dx=0; p->dy=0;
           }

       if (a->name=="player" && b->name=="powerup")
       if ( isCollide(a,b) )
           {
            b->life=false;
            reinterpret_cast<player*>(a)->addBullets();
            //p->life=false;
           }
    }
}

void Game::SetAnimations(){
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

    background.setTexture(Background);

    sExplosion.Settings(RockExplosion, 0,0,256,256, 48, 0.5);
    sRock.Settings(Rock, 0,0,64,64, 16, 0.2);
    sRock_small.Settings(RockSmall, 0,0,64,64, 16, 0.2);
    sBullet.Settings(FireBlue, 0,0,32,64, 16, 0.8);
    sPlayer.Settings(Spaceship, 40,0,40,40, 1, 0);
    sPlayer_go.Settings(Spaceship, 40,40,40,40, 1, 0);
    sExplosion_ship.Settings(ShipExplosion, 0,0,192,192, 64, 0.5);
    sBulletPowerup.Settings(BulletPowerup, 0,0,32,64, 16, 0.8);
}

void Game::Update(){
    if (p->thrust)  p->anim = sPlayer_go;                    //FIRE WHILE THURSTING
    else   p->anim = sPlayer;

    for(auto e:entities)
     if (e->name=="explosion")                               //EXPLOSIONS TO END
      if (e->anim.isEnd()) e->life=0;

    if (rand()%200==0){                                      // RANDOMLY CREATE ASTEROIDS; 200 - IS AN ASTEROIDS FREQUENCY
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
}


void Game::InitialAster(){
    for(int i=0;i<15;i++)
    {
      asteroid *aster = new asteroid();
      aster->settings(sRock, rand()%W, rand()%H, rand()%260, 25);
      entities.push_back(aster);
    }
}

void Game::CreatePlayer(){
    p->settings(sPlayer,H/2,W/2,0,20);
    entities.push_back(p);
}


