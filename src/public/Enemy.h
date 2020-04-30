#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <Pawn.h>

using namespace std;
using namespace sf;

class Enemy: public Pawn {
    public:
        Enemy();
        void TakeDamage(float damage, Actor* dmgCauser, string damage_type);
        bool IsAlive(); // This should go to an interface or to parent PAWN class

        bool Attack();
        void Update(float delta);
        void Draw(double percent, double delta );
        void OnActorOverlap(Actor *otherActor);

        void ToggleTarget(bool Active);

    private:
        SSprite* TargetMarker;
        void PrepareMarker();
};

#endif