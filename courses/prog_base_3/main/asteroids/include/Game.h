#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include <list>
#include "Animation.h"
#include "Entity.h"
#include "asteroid.h"
#include "bullet.h"
#include "player.h"
#include "powerup.h"

using namespace sf;

class Game
{
    public:
        Game();

        Event event;

        player * p;

        Animation sExplosion;
        Animation sRock;
        Animation sRock_small;
        Animation sBullet;
        Animation sPlayer;
        Animation sPlayer_go;
        Animation sExplosion_ship;
        Animation sBulletPowerup;

        Sprite background;

        std::list<Entity*> entities;

        void CheckColisions();
        void Update();

    protected:

    private:
        void SetAnimations();
        void InitialAster();
        void CreatePlayer();
};

#endif // GAME_H
