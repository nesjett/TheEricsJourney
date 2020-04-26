#pragma once
#ifndef TILE_H
#define TILE_H
#include <Actor.h>
#include <Engine.h>

using namespace std;
using namespace sf;

class Tile: public Actor {
    public:
        Tile(string nombreSprite, float x, float y, float widthSprite, float heightSprite, ObjectType tipo);
        float width, height;
        void Update(float delta);
        void Draw(double percent, double delta );
        Faction getFaction(){ return faction; };
        void setFaction(Faction f){ faction = f; };
        void OnActorOverlap(Actor *otherActor);
    protected:
        void PrepareSprite();
        Animation* animation;
    private:
        string texture_file;
        Faction faction;
};

#endif