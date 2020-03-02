#include <string>
using namespace std;
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#pragma once


class MiModulo{
    
    public:
        MiModulo();

        string texture_file;
        sf::Sprite sprite;

        float location[2];
        float direction[2];

        float movementSpeed = 2;


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

    protected:
        void PrepareSprite();

        // Apply dying effects
        void Die();
        // Apply hit effects on takeDamage()
        void ApplyHitEffects(string effect); // TODO: effect should be a class of type damage_type, not  astring
};