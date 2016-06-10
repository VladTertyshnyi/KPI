#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#include <string>
#include <cstring>

class Table
{
    public:
        Table(){
            }


        struct member{
            std::string name;
            int time;
        };

        struct member members[10] = {
           {
              "Name", 10
           },

           {
              "Name", 10
           },

           {
              "Name", 10
           },

           {
              "Name", 10
           },

           {
              "Name", 10
           },

           {
              "Name", 10
           },

           {
              "Name", 10
           },

           {
              "Name", 10
           },

           {
              "Name", 10
           },

           {
              "Name", 10
           }
        };

        int maxSize = 10;

        bool isInsert(int value){
            if (members[maxSize - 1].time < value) return true;
            else return false;
        }

        void add(std::string name, int time){
            int index = -1;
            for(int i = maxSize -1; i >= 0; i--){
                if(time > members[i].time)continue;else{
                    if(i == maxSize -1) return;else{ index = i; break;}
                }
            }
            if(index == -1)index = 0;
            for(int i = maxSize-1; i > index; i--){
                members[i].name = members[i-1].name;
                members[i].name = members[i-1].name;
            }
            members[index].name = name;
            members[index].time = time;

        }



    protected:

    private:
};

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

    Texture tSpaceship,
            tBackground,
            tRockExplosion,
            tRock,
            tFireBlue,
            tFireRed,
            tRockSmall,
            tShipExplosion,
            tBulletPowerup;
    ///////LOADING TEXTURES FROM FILES//////
    tSpaceship.loadFromFile("images/spaceship.png");
    tBackground.loadFromFile("images/background.jpg");
    tRockExplosion.loadFromFile("images/explosions/type_C.png");
    tRock.loadFromFile("images/rock.png");
    tFireBlue.loadFromFile("images/fire_blue.png");
    tRockSmall.loadFromFile("images/rock_small.png");
    tShipExplosion.loadFromFile("images/explosions/type_B.png");
    tBulletPowerup.loadFromFile("images/fire_red.png");

    tSpaceship.setSmooth(true);
    tBackground.setSmooth(true);

    Sprite background(tBackground);

    Animation aExplosion(tRockExplosion, 0,0,256,256, 48, 0.5);
    Animation aRock(tRock, 0,0,64,64, 16, 0.2);
    Animation aRock_small(tRockSmall, 0,0,64,64, 16, 0.2);
    Animation aBullet(tFireBlue, 0,0,32,64, 16, 0.8);
    Animation aPlayer(tSpaceship, 40,0,40,40, 1, 0);
    Animation aPlayer_go(tSpaceship, 40,40,40,40, 1, 0);
    Animation aExplosion_ship(tShipExplosion, 0,0,192,192, 64, 0.5);
    Animation aBulletPowerup(tBulletPowerup, 0,0,32,64, 16, 0.8);
    /////////////////MAIN GAME OBJECTS//////////////////////////////
    std::list<Entity*> entities;

    for(int i=0;i<10;i++)
    {
      asteroid *aster = new asteroid();
      aster->settings(aRock, rand()%W, rand()%H, rand()%260, 25);
      entities.push_back(aster);
    }

    Table table;
    std::string userInput;
    sf::String sfUserInput;


    player *p = new player();
    p->settings(aPlayer,W/2,H/2, 0, 20);
    p->anim.sprite.setColor(Color::Red);
    entities.push_back(p);


    //////////////////////CLOCK AND TIME VARIABLES//////////////////
    Clock gameClock;
    gameClock.restart();
    int gameTime = 0;

    Clock notifClock;
    notifClock.restart();

    int notifTime = 0;
    int notifMax = 3;
    //////////////////TEXT VARIABLES/////////////////////////////
    Font font;
	font.loadFromFile("font.ttf");
	Text text("", font, 20);
	text.setColor(Color::Blue);
	text.setStyle(Text::Bold);
    Text time("", font, 20);
    time.setStyle(Text::Bold);
    time.setPosition(130, 40);
    text.setPosition(40, 40);
    Text newRecord("NEW RECORD!!!\n\n\nEnter your name\nthen press enter:", font, 15);
    newRecord.setColor(Color::White);
    newRecord.setPosition(W/2 - 120, H/2 - 250);
    Text notif("", font, 40);
    notif.setStyle(Text::Bold);
    notif.setPosition(W/2 - 40, H/2 - 100);
    Text TableString("", font, 20);
    TableString.setPosition(W/2 - 100, H/2 - 250);
    std::stringstream gameTimeString;
    std::stringstream gameTimeStrBig;
    std::stringstream tableRank;
    std::string input;
    sf::Text sfInput("", font, 40);
    sfInput.setPosition(W/2 - 100, H/2 - 100);

    /////////////////////////////////MUSIC AND SOUNDS//////////////////////////////////
    Music music;
    music.openFromFile("music.ogg");
    music.play();
    music.setLoop(true);

    SoundBuffer buffer;
    buffer.loadFromFile("powerup.wav");
    Sound powerupS;
    powerupS.setBuffer(buffer);

    SoundBuffer buffer1;
    buffer1.loadFromFile("explode.wav");
    Sound explodeS;
    explodeS.setBuffer(buffer1);

    SoundBuffer buffer2;
    buffer2.loadFromFile("meteor.wav");
    Sound meteorS;
    meteorS.setBuffer(buffer2);


    ///////////////////////////////////DRAW OBJECTS//////////////////////////////////
    RectangleShape tableRect(Vector2f(W/2 -300, H/2 + 200));
    tableRect.setFillColor(Color::Blue);
    Color tmp = tableRect.getFillColor();
    tmp.a = 160;
    tableRect.setOutlineThickness(5);
    tableRect.setOutlineColor(Color::White);
    tableRect.setFillColor(tmp);
    tableRect.setOrigin(tableRect.getSize().x / 2, tableRect.getSize().y / 2);
    tableRect.setPosition(W/2, H/2);

    /////////////////////////////////VARIABLES TO SAVE DATA AND TIME//////////////////
    int notifValue = 0;
    bool showRecord= 0;
    int recordTime = 0;
    bool showTable;
    int isDied = 0;

    /////////////////MAIN GAME LOOP////////////////////////
    while (app.isOpen())
    {
        Event event;
        isDied = false;
        showTable = false;
/////////////////////////HANDLE INPUT/////////////////////
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();

            if (event.type == Event::KeyReleased)
             if (event.key.code == Keyboard::Space)
              {
                  if(p->getPowerUpStatus()== 0){
                        bullet *b0 = new bullet();
                        b0->settings(aBullet,p->x,p->y,p->angle,10);
                        entities.push_back(b0);
                  }
                  else if(p->getPowerUpStatus()== 1){
                        bullet *b1 = new bullet();
                        b1->settings(aBullet,p->x,p->y,p->angle - 10,10);
                        entities.push_back(b1);
                        bullet *b2 = new bullet();
                        b2->settings(aBullet,p->x,p->y,p->angle + 10,10);
                        entities.push_back(b2);
                  }
                   else if(p->getPowerUpStatus()== 2){
                        bullet *b3 = new bullet();
                        b3->settings(aBullet,p->x,p->y,p->angle - 15,10);
                        entities.push_back(b3);
                        bullet *b4 = new bullet();
                        b4->settings(aBullet,p->x,p->y,p->angle + 15,10);
                        entities.push_back(b4);
                        bullet *b5 = new bullet();
                        b5->settings(aBullet,p->x,p->y,p->angle ,10);
                        entities.push_back(b5);
                   } else{
                        bullet *b6 = new bullet();
                        b6->settings(aBullet,p->x,p->y,p->angle,10);
                        entities.push_back(b6);
                   }
              }
            if (event.type == sf::Event::TextEntered)
            {

                if (event.text.unicode < 128  && showRecord)
                {
                    input += static_cast<char>(event.text.unicode);
                    sfInput.setString(input);
                }
            }
        }

    if (Keyboard::isKeyPressed(Keyboard::Right)) p->angle+=p->turnSpeed;
    if (Keyboard::isKeyPressed(Keyboard::Left))  p->angle-=p->turnSpeed; // CREATE FIELD TURN SPEED
    if (Keyboard::isKeyPressed(Keyboard::Up)) p->thrust=true;else p->thrust=false;
    if (Keyboard::isKeyPressed(Keyboard::Tab)) showTable = true; //TO DO: ADD POWERUPS THAT GIVE U BIGGER INERTION AND turn SPEED
    if (Keyboard::isKeyPressed(Keyboard::Return) && showRecord == true) {showRecord = false;
                                                    table.add(input, recordTime);
                                                    recordTime = 0;
                                                    sfInput.setString("");
                                                    input.clear();}

 // CHECKING THE COLLISION BETWEEN ASTEROIDS AND BULLETS, PLAYER AND ASTEROIDS, PLAYER AND POWERUPS//////
    for(auto a:entities)
     for(auto b:entities)
    {
      if (a->name=="asteroid" && b->name=="bullet")
       if ( isCollide(a,b) )
           {
            a->life=false;
            b->life=false;

            Entity *e = new Entity();
            e->settings(aExplosion,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            meteorS.play();

            if(rand()%100 > 95){
            powerup *pow = new powerup();
            pow->settings(aBulletPowerup,a->x,a->y, rand()%360, 15);
            pow->name = "powerupBull";
            entities.push_back(pow);
            }else{
                if(rand()%100 > 95){
                powerup *pow = new powerup();
                pow->settings(aBulletPowerup,a->x,a->y, rand()%360, 15);
                pow->anim.sprite.setColor(Color::Cyan);
                pow->name = "powerupStats";
                entities.push_back(pow);
                }
            }

            for(int i=0;i<2;i++)
            {
             if (a->R==15) continue;
             Entity *e = new asteroid();
             e->settings(aRock_small,a->x,a->y,rand()%360,15);
             entities.push_back(e);
            }

           }

      if (a->name=="player" && b->name=="asteroid")
       if ( isCollide(a,b) )
           {
            gameClock.restart();
            explodeS.play();
            isDied = 1;
            reinterpret_cast<player*>(a)->reset();
            b->life=false;
            //p->life=false;
            Entity *e = new Entity();
            e->settings(aExplosion_ship,a->x,a->y);
            e->name="explosion";
            entities.push_back(e);

            p->settings(aPlayer,rand()%W,rand()%H,rand()%360,20);
            p->dx=0; p->dy=0;
           }

       if (a->name=="player" && b->name=="powerupBull")
       if ( isCollide(a,b) )
           {
            b->life=false;
            reinterpret_cast<player*>(a)->addBullets();
            powerupS.play();
            //p->life=false;
           }
       if (a->name=="player" && b->name=="powerupStats")
       if ( isCollide(a,b) )
           {
            b->life=false;
            reinterpret_cast<player*>(a)->addStats();
            powerupS.play();
            //p->life=false;
           }
    }


    if (p->thrust)  p->anim = aPlayer_go;                    //FIRE WHILE THURSTING
    else   p->anim = aPlayer;

    for(auto e:entities)
     if (e->name=="explosion")                               //EXPLOSIONS TO END
      if (e->anim.isEnd()) e->life=0;

    if (rand()%100 < p->asteroidFrequency){                  //RANDOMLY CREATE ASTEROIDS
       asteroid *a = new asteroid();
       a->settings(aRock, 0,rand()%H, rand()%360, 25);
       entities.push_back(a);
     }

    for(auto i=entities.begin();i!=entities.end();)          //UPDATE ALL ENTITIES IN THE GAME
    {
      Entity *e = *i;

      e->update();
      e->anim.update();

      if (e->life==false) {i=entities.erase(i); delete e;}
      else i++;
    }

    ////////CHECK FOR NEW RECORD////////////////////////
    if(isDied  && table.isInsert(gameTime)){
       showRecord = true;
       recordTime = gameTime;
    }

    //////////////////////////////Table String UPDATE///////////////////////////
    tableRank.str("");
    tableRank <<  "  RECORDS"<< std::endl << "    TABLE" << std::endl << std::endl;
    for(int i = 0; i < 10; i++){
        tableRank << i + 1 << ". " << table.members[i].name << " " << table.members[i].time << std::endl << std::endl;
    }
    TableString.setString(tableRank.str());
    ///////////////////////////Notification/////////////////////////////////
    if(isDied && gameTime>5){
        notifValue =  gameTime;
        notifTime = 0;
        notifClock.restart();
        gameTimeStrBig.str("");
        gameTimeStrBig << notifValue;
        gameTimeStrBig << " sec.";
        notif.setString(gameTimeStrBig.str());
    }

    if(notifTime < 3){
        notifTime = (int)notifClock.getElapsedTime().asSeconds();
    }else{
        notifClock.restart();
        gameTimeStrBig.str("");
        notif.setString(gameTimeStrBig.str());
    }
    //////////////////////gameTime/////////////////////
    gameTime = (int)gameClock.getElapsedTime().asSeconds();
    gameTimeString.str(" ");
    gameTimeString << gameTime;
    text.setString("Time:");
    time.setString(gameTimeString.str());
    //////////////////draw all objects/////////////////////////
    app.draw(background);
    app.draw(notif);
    if(notifTime < notifMax){
        app.draw(notif);
    }else{
        notifClock.restart();
    }
   for(auto i:entities)
     i->draw(&app);

    app.draw(text);
    app.draw(time);
    if(showTable){
        app.draw(tableRect);
        app.draw(TableString);
    }
    ///////////////Draw record////////////////
    if(showRecord && !showTable){
        app.draw(tableRect);
        app.draw(newRecord);
        app.draw(sfInput);
    }

    app.display();
    }

    return 0;
}



