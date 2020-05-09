#pragma once
#ifndef PAWN_H
#define PAWN_H
#include <Actor.h>
#include <Engine.h>
#include <list>

using namespace std;
using namespace sf;

class Pawn: public Actor {
    public:
        Pawn();
        Vector2f direction;

        /* Scalar usually between 0 and 1 */
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
        void Update(float delta);
        void Draw(double percent, double delta );
        Faction getFaction(){ return faction; };
        void setFaction(Faction f){ faction = f; };
        void OnActorOverlap(Actor *otherActor);

        void SetDirection(Vector2f NewDir) { LastDirection = direction; direction = NewDir; };
        Vector2f GetLastDirection() { return LastDirection; };
        Vector2f GetDirection() { return direction; };
    protected:
        void PrepareSprite();

        virtual void SetAnimation();

        // Apply dying effects
        virtual void Die();
        // Apply hit effects on takeDamage()
        virtual void ApplyHitEffects(string effect); // TODO: effect should be a class of type damage_type, not  astring
        Animation* activeAnim = NULL;
        std::map<std::string, Animation*> Animations;
        Actor* DirectionPrecheck(Vector2f loc, ObjectType type);
        Actor* DirectionPrecheck(Vector2f loc, ObjectType type, list<Actor*> ActorsToIgnore, int Axis);
        sf::RectangleShape movementTraceDebug;
        Faction faction;
    private:
        string texture_file;

        Actor *BloquedX = nullptr;
        Actor *BloquedY = nullptr;

        Vector2f velocity = Vector2f(0.f, 0.f);
        Vector2f LastDirection;
};

#endif