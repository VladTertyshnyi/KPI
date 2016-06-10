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
        bool hasLost;
        int statStatus;
        float acceleration;

        void reset();
        void update();
        void addBullets();
        void addStats();
        int getPowerUpStatus();
        bool HasLost();
    protected:

    private:
};

#endif // PLAYER_H
