#ifndef BULLET_H
#define BULLET_H

#include <Entity.h>


class bullet : public Entity
{
    public:
        bullet();
        void update();
        int speed;

    protected:

    private:
};

#endif // BULLET_H
