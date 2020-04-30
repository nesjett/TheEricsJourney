#pragma once
#ifndef SPIKES_H
#define SPIKES_H
#include <Trap.h>
#include <Engine.h>

using namespace std;
using namespace sf;

class Spikes: public Trap {
    public:
        Spikes();

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