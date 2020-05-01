#pragma once
#ifndef MEJORA_H
#define MEJORA_H
#include <Actor.h>
#include <Engine.h>

using namespace std;
using namespace sf;

class Mejora: public Actor {
    public:
        Mejora(PowerUpType tipo);
        ~Mejora();

        string nombre;
        PowerUpType tipoMejora;
        void Update(float delta);
        void OnActorOverlap(Actor *otherActor);
    protected:
        virtual void PrepareSprite();
    private:
        std::string texture_file;
};

#endif