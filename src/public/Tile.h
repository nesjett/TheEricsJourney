#pragma once
#ifndef TILE_H
#define TILE_H
#include <Actor.h>
#include <Engine.h>

using namespace std;
using namespace sf;

/*
 * Clase que utilizaremos para los muros
 */

class Tile: public Actor {
    public:
        Tile(string nombreSprite, float x, float y, float widthSprite, float heightSprite, ObjectType tipo, bool puerta);
        float width, height;
        void Update(float delta);
        void Draw(double percent, double delta );
        void OnActorOverlap(Actor *otherActor);
        bool esPuerta;
    protected:
        virtual void PrepareSprite();
    private:
        string texture_file;
};

#endif