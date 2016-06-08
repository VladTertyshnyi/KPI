#ifndef POWERUP_H
#define POWERUP_H

#include <Entity.h>


class powerup : public Entity
{
    public:
        int speed;
        powerup();
        void update();

    protected:

    private:
};

#endif // POWERUP_H
