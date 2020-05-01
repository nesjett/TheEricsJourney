#pragma once
#ifndef SAW_H
#define SAW_H
#include <Trap.h>
#include <Engine.h>
#include <memory>

using namespace std;
using namespace sf;

class Saw: public Trap {
    public:
        Saw(Vector2f Loc, float Length);

        void Update(float delta);
        void Draw(double percent, double delta );
        void OnActorOverlap(Actor *otherActor);
    protected:
        virtual void PrepareSprite();

        Animation* activeAnim = NULL;
        std::map<std::string, Animation*> Animations;

        // creates the rail sprites for visuals only
        void CreateRail();
    private:
        std::string texture_file;
        float movementSpeed;
        Vector2f direction;
        Vector2f initialLocation;
        float trapLength;
        vector<unique_ptr<SSprite>> rail;
};

#endif