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
enum ObjectType { worldstatic=0, worlddynamic=1, pawn=2, projectile=3, trap=4, blocker=5, powerup=6, door=7 }; // NOTA: Parece que c++ no permite que los nombres de una enum tengan mayusculas!!
enum PowerUpType { health=0, movementspeed=1, attackspeed=2, attackmore=3 };
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
        void setView(float centerY, float borderX);
        void resetView();
    protected:
        Engine();
        Engine(const Engine &);
        Engine &operator= (const Engine &);
        virtual ~Engine();
        //std::map<std::string, sf::Texture> LoadedTextures;
    private:
        static Engine* pInstance;
        sf::RenderWindow app;
        std::string oTypeNames[5] = {"WorldStatic", "WorldDynamic", "Pawn", "Projectile", "Trap"};
        sf::View vista;
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
        // Returns a pointer to the SFML sprite
        sf::Sprite getSprite(){ return sfsprite; }
        // Returns a ref to the SFML sprite
        sf::Sprite &getSpriteR(){ return sfsprite; }
        virtual sf::Vector2f Draw();
        virtual sf::Vector2f Draw(sf::Vector2f location, sf::Vector2f location_prev, double percent);
        void setOrigin(double x, double y);
        void setTextureRect(double x, double y, double w, double h);
        void setTextureRect(sf::IntRect rect);
        void setScale(double x, double y);
        sf::FloatRect getGlobalBounds();
        sf::FloatRect getBounds();
        sf::FloatRect setBounds(float newScale);
        sf::Texture LoadTexture(string path);
    protected:
        sf::Texture texture;
        sf::Sprite sfsprite;
    private:
        Engine *eng;
        sf::FloatRect GlobalBounds;
        std::string TextPath; // Used for debug, to check whther we are loading a specific texture file

};



/***********************
 * 
 * CLASS: ANIMATION
 * 
 * **********************/
// Bsed on source: https://github.com/SFML/SFML/wiki/Easy-Animations-With-Spritesheets
class Animation {
    std::vector<AnimFrame> frames;
    double totalLength;
    int progress;
    sf::Sprite &target;
    int duration;
    int currentFrame;

    public:
        Animation(sf::Sprite &target, int length);
        Animation(sf::Sprite &target, int length, bool looping);
        virtual ~Animation();
        void Reset();
        void addFrame(AnimFrame&& frame); // TODO: Could forget about this if we add a standard size for the rect in the constructor, and a default rate.
        
        // Returns the remaining animation time in ms
        int update(double elapsed); 
        double getLength() const { return totalLength; }
    private:
        bool loop = false;
        int totalProgress;
};



/***********************
 * 
 * CLASS: CASCADE. Very Basic particle system
 * This class spawns a animated ssprite with some specific parameters.
 * Does not have movement capabilities.
 * Determined lifespan since creation.
 * 
 * **********************/
class Cascade : public SSprite {
    public:
        Cascade();
        Cascade(sf::Vector2f loc);
        
        // Total lifetime of the emitter
        void SetLifetime(int time);

        // Update animation state if any and draw sprite to canvas
        void Draw(double delta);
        
        // By default = true. Sets if the particle should loop infinite time
        void SetAuto(bool Auto);

        int GetRemainingLife();
        bool IsPendingDelete() {return PendingDelete;};
        virtual ~Cascade();
    protected:
        Animation *Anim;
        sf::Clock LifeCounter;
    private:
        bool AutoDestroy;
        int Lifetime; // As milliseconds
        bool PendingDelete;
};




/***********************
 * 
 * CLASS: TText. Simple text with lifetime
 * 
 * **********************/
class TText {
    public:
        TText(sf::String txtString, sf::Vector2f Location, float Lifetime);
        virtual ~TText();
        virtual void Draw(float delta);
        long getDeathTime() { return DeathTime; };

    private:
        Engine *eng;
        //game *gi;
        long DeathTime;
        long CreationTime;
        sf::Font *font;
        sf::Text text;
};



#endif 