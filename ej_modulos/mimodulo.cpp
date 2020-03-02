#include "mimodulo.h"

#include <iostream>

MiModulo::MiModulo() {
    std::cout << "Enemy spawned..." << std::endl;  

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

   

}


void MiModulo::TakeDamage(float damage, string damage_type){
    std::cout << "Damage taken!" << std::endl; 
    if(health_Current > 0){ // Only apply damage if the enemy is alive.
        health_Current-=damage;
        if(IsAlive() == false){
            Die();
        } else {
            ApplyHitEffects(damage_type); // Apply hit effects
        }
    }
}

bool MiModulo::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void MiModulo::Die(){
    std::cout << "Enemy died!" << std::endl; 
}
