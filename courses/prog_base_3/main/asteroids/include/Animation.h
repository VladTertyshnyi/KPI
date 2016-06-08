#ifndef ANIMATION_H
#define ANIMATION_H
#include <SFML/Graphics.hpp>
#include <list>
using namespace sf;

class Animation
{
    public:
        Animation();
        float Frame, speed;
        Sprite sprite;
        std::vector<IntRect> frames;

        Animation (Texture &t, int x, int y, int w, int h, int count, float Speed);
        void update();
        bool isEnd();
        void Settings(Texture &t, int x, int y, int w, int h, int count, float Speed);
        virtual ~Animation();

    protected:

    private:
};

#endif // ANIMATION_H
