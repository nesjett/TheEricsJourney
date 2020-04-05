#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
//#include <Actor.h>
#include <iostream>
//#include <algorithm>

using namespace std;

struct AnimFrame {
   sf::IntRect rect;
   double duration; // in milliseconds
};

enum Faction { enemy=2, allie=1, neutral=0 };
enum ObjectType { worldstatic=0, worlddynamic=1, pawn=2, projectile=3, trap=4 }; // NOTA: Parece que c++ no permite que los nombres de una enum tengan mayusculas!!

/***********************
 * 
 * CLASS: ENGINE
 * 
 * **********************/
class Engine
{
    public:
        static Engine* Instance();
        void init(/*char*, int*/);
        sf::RenderWindow &getApp(){ return app; }
        sf::RenderWindow &CreateApp(sf::VideoMode vm, string wn);
        std::string getObjectType(ObjectType type) { if(type <= sizeof(oTypeNames)) { return oTypeNames[type]; } };
    protected:
        Engine();
        Engine(const Engine &);
        Engine &operator= (const Engine &);
        virtual ~Engine();
    private:
        static Engine* pInstance;
        sf::RenderWindow app;
        std::string oTypeNames[5] = {"WorldStatic", "WorldDynamic", "Pawn", "Projectile", "Trap"};
};



/***********************
 * 
 * CLASS: SPRITE
 * 
 * **********************/
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
        sf::Vector2f Draw(sf::Vector2f location, sf::Vector2f location_prev, double percent);
        void setOrigin(double x, double y);
        void setTextureRect(double x, double y, double w, double h);
        void setTextureRect(sf::IntRect rect);
        void setScale(double x, double y);
    protected:
        sf::Texture texture;
        sf::Sprite sfsprite;
    private:
        Engine *eng;

};


/***********************
 * 
 * CLASS: ANIMATION
 * 
 * **********************/
// Source: https://github.com/SFML/SFML/wiki/Easy-Animations-With-Spritesheets
class Animation {
    std::vector<AnimFrame> frames;
    double totalLength;
    double progress;
    sf::Sprite &target;

    public:
        Animation(sf::Sprite &target);
        Animation(sf::Sprite &target, bool looping);
        virtual ~Animation();
        void addFrame(AnimFrame&& frame); // TODO: Could forget about this if we add a standard size for the rect in the constructor, and a default rate.
        void update(double elapsed); 
        const double getLength() const { return totalLength; }
    protected:
        bool loop = false;
};




#endif 