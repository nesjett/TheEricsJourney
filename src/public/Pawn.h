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
        SSprite *sprite;
        Vector2f direction;

        float movementSpeed;

        /************************************************************
         * ENEMIGO START
         * **************************************************/

        float health_MAX;
        float health_Current;

        float damage_Base;
        float damage_Multiplier; 


        void TakeDamage(float damage, string damage_type);
        bool IsAlive(); // This should go to an interface or to parent PAWN class

        // Adds movement to the desired direction
        void UpdateMovement(); 

        sf::CircleShape bala = sf::CircleShape(5);

        bool Attack();

        void Update(float delta);
        void Draw(float percent);

    protected:
        Clock cD, cInterp, cMov;

        void PrepareSprite();

        // Apply dying effects
        void Die();
        // Apply hit effects on takeDamage()
        void ApplyHitEffects(string effect); // TODO: effect should be a class of type damage_type, not  astring
    private:
        string texture_file;
};

#endif