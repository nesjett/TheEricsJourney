#pragma once
#ifndef TRAP_H
#define TRAP_H
#include <Actor.h>
#include <Engine.h>

using namespace std;
using namespace sf;

class Trap: public Actor {
    public:
        Trap();

        void Update(float delta);
        void Draw(double percent, double delta );
        void OnActorOverlap(Actor *otherActor);
    protected:
        virtual void PrepareSprite();

        float damage_factor;
        
        Actor *target;
        Animation* activeAnim = NULL;
        std::map<std::string, Animation*> Animations;
        sf::Clock timer;
    private:
        std::string texture_file;
};

#endif