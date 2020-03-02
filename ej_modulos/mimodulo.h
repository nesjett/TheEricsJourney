#include <string>
using namespace std;
#pragma once


class MiModulo{
    
    public:
        MiModulo();

        /************************************************************
         * ENEMIGO START
         * **************************************************/

        float health_MAX;
        float health_Current;

        float damage_Base;
        float damage_Multiplier; 


        void TakeDamage(float damage);
        bool IsAlive(); // This should go to an interface or to parent PAWN class

        // Adds movement to the desired direction
        void AddMovement(); 

    protected:
        // Apply dying effects
        void Die();
        // Apply hit effects on takeDamage()
        void ApplyHitEffects(string effect); // TODO: effect should be a class of type damage_type, not  astring
};