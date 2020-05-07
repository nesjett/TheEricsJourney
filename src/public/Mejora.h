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

        string nombre;
        PowerUpType tipoMejora;
        void Update(float delta);
        void Draw(double percent, double delta);
        void OnActorOverlap(Actor *otherActor);
        bool activada;
        bool utilizada;
        Sprite getSprite();
    protected:
        virtual void PrepareSprite();
    private:
        std::string texture_file;
        SSprite *dialog;
};

#endif