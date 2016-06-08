#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>


class player : public Entity
{
    public:
        player();

        int PowerUpStatus;
        float asteroidFrequency;
        float inertion;
        int maxSpeed;
        float turnSpeed;
        bool thrust;
        int statStatus;

        void reset();
        void update();
        void addBullets();
        void addStats();
        int getPowerUpStatus();

    protected:

    private:
};

#endif // PLAYER_H
