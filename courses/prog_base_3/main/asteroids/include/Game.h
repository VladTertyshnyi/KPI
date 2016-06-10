#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Window.h"
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

class Game{
public:
    Game();
    ~Game();

    void HandleInput();
    void Update();
    void Render();
    gameWindow * GetWindow();
    Time GetElapsed();
    void RestartClock();

    gameWindow window;

    player *p;

    std::list<Entity*> entities;

    //Font font;
    Text text;
    Text time;
    Text notif;

    std::stringstream gameTimeString;
    std::stringstream gameTimeStrBig;

    int gameTime;
    Clock gameClock;

    Texture tSpaceship,
            tBackground,
            tRockExplosion,
            tRock,
            tFireBlue,
            tFireRed,
            tRockSmall,
            tShipExplosion,
            tBulletPowerup;

    Sprite background;

    Animation aExplosion,
            aRock,
            aRock_small,
            aBullet,
            aPlayer,
            aPlayer_go,
            aExplosion_ship,
            aBulletPowerup;

    Music music;

    SoundBuffer buffer;
    SoundBuffer buffer1;
    SoundBuffer buffer2;

    Sound powerupS;
    Sound explodeS;
    Sound meteorS;





private:

};



#endif // GAME_H_INCLUDED
