#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
//#include <game.h>
#include <iostream>
//#include <algorithm>

using namespace std;

struct AnimFrame {
   sf::IntRect rect;
   double duration; // in milliseconds
};

//enum faction { enemy=2, allie=1, neutral=0 };


class Engine
{
    public:
        static Engine* Instance();
        void init(/*char*, int*/);
        sf::RenderWindow &getApp(){ return app; }
        sf::RenderWindow &CreateApp(sf::VideoMode vm, string wn);
    protected:
        Engine();
        Engine(const Engine &);
        Engine &operator= (const Engine &);
        virtual ~Engine();
    private:
        static Engine* pInstance;
        sf::RenderWindow app;
};




// Super Sprite (interface class)
class SSprite
{
    public:
        SSprite(string TexturePath);
        SSprite();
        ~SSprite();
        void setRotation(double angle);
        void setPosition(double x, double y);
        sf::Sprite getSprite(){
            return sfsprite;
        }
        sf::Sprite &getSpriteR(){ return sfsprite; }
        void Draw(sf::Vector2f location, sf::Vector2f location_prev, double percent);
        void setOrigin(double x, double y);
        void setTextureRect(double xx, double xy, double yx, double yy);
        void setScale(double x, double y);
    protected:
        sf::Texture texture;
        sf::Sprite sfsprite;
    private:
        Engine *eng;

};



class Animation {
    std::vector<AnimFrame> frames;
    double totalLength;
    double progress;
    sf::Sprite &target;

    public:
        Animation(sf::Sprite &target);
        virtual ~Animation();
        void addFrame(AnimFrame&& frame);
        void update(double elapsed); 
        const double getLength() const { return totalLength; }
};




#endif 