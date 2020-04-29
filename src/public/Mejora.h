#pragma once
#ifndef PAWN_H
#define PAWN_H
#include <Actor.h>
#include <Engine.h>

using namespace std;
using namespace sf;

class Mejora: public Actor {
    public:
        Mejora();
        ~Mejora();

        float damage_Base;

        void Update(float delta);
        void Draw(double percent, double delta );
        void OnActorOverlap(Actor *otherActor);
    protected:
        virtual void PrepareSprite();

        Animation* activeAnim = NULL;
        std::map<std::string, Animation*> Animations;
    private:
        std::string texture_file;
};

#endif