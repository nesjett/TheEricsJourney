#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Animation
{
    public:
        Animation();
        virtual ~Animation();
        void setAnimation(char* nTextura, IntRect firstF, IntRect finalF, int incremento,float tiempo);
        //void update(Vector2f movement, float mTime);
        void update();
        Sprite sprite;

    private:
        Texture texture;
        IntRect firstF;
        IntRect finalF;
        IntRect actualFrame;
        int incremento;
//        float totalTime;
        float switchTime;
        sf::Clock clock;

};

#endif