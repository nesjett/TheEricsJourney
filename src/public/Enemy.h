#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <Pawn.h>
#include <list>

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
        void ApplyHitEffects(string effect);

        void ToggleTarget(bool Active);

    protected: 
        list<TText> HitText;

    private:
        SSprite* TargetMarker;
        void PrepareMarker();
        bool Targetted;
};

#endif