#pragma once
#ifndef DOOR_H
#define DOOR_H
#include <Actor.h>
#include <Engine.h>

using namespace std;
using namespace sf;

class Door: public Actor {
    public:
        Door(Vector2f position, bool esPuertaSuperior);
        void Update(float delta);
        void Draw(double percent, double delta);
        void OnActorOverlap(Actor *otherActor);
        bool abierta;
        bool superior;
        void openDoor();
    protected:
        virtual void PrepareSprite();
    private:
        std::string texture_file;
        Animation* activeAnim = NULL;
};

#endif