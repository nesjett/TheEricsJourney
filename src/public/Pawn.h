#pragma once
#ifndef PAWN_H
#define PAWN_H
#include <Actor.h>
#include <Engine.h>

using namespace std;
using namespace sf;

class Pawn: public Actor {
    public:
        Pawn();
        Vector2f direction;

        float movementSpeed;

        /************************************************************
         * ENEMIGO START
         * **************************************************/

        float health_MAX;
        float health_Current;

        float damage_Base;
        float damage_Multiplier; 


        void TakeDamage(float damage, Actor* dmgCauser, string damage_type);
        bool IsAlive(); // This should go to an interface or to parent PAWN class

        bool Attack();
        void SetAnimation();
        void Update(float delta);
        void Draw(double percent, double delta );
        Faction getFaction(){ return faction; };
        void setFaction(Faction f){ faction = f; };
        void OnActorOverlap(Actor *otherActor);
    protected:
        void PrepareSprite();

        // Apply dying effects
        void Die();
        // Apply hit effects on takeDamage()
        virtual void ApplyHitEffects(string effect); // TODO: effect should be a class of type damage_type, not  astring
        Animation* activeAnim = NULL;
        std::map<std::string, Animation*> Animations;
        Actor* DirectionPrecheck(Vector2f loc, ObjectType type);
        sf::RectangleShape movementTraceDebug;
        Faction faction;
    private:
        string texture_file;
};

#endif