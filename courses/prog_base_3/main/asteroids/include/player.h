#ifndef PLAYER_H
#define PLAYER_H

#include <Entity.h>


class player : public Entity
{
    public:
        player();
        bool thrust;
        void update();

    protected:

    private:
};

#endif // PLAYER_H
