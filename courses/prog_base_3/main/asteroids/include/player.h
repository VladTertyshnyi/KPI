#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>


class player : public Entity
{
    public:
        int PowerUpStatus;
        player();
        bool thrust;
        void update();
        void addBullets();
        int getPowerUpStatus();

    protected:

    private:
};

#endif // PLAYER_H
