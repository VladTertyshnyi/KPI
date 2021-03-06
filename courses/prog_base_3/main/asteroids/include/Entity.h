#ifndef ENTITY_H
#define ENTITY_H
#include "Animation.h"
#include <SFML/Graphics.hpp>
#define DEGTORAD 0.017453

const int W = 1200;
const int H = 700;



using namespace sf;

class Entity
{
    public:
        Entity();

        float x,y,dx,dy,R,angle;
        bool life;
        std::string name;
        Animation anim;

        void settings(Animation &a,int X,int Y,float Angle=0,int radius=1);
        virtual void update();
        void draw(RenderWindow * app);

        virtual ~Entity();

    protected:

    private:
};

#endif // ENTITY_H
