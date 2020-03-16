#include "../public/Enemy.h"

void Enemy::Update(float delta){
    //std::cout << "Iniciamos UPDATE()" << std::endl;

}

void Enemy::TakeDamage(float damage, string damage_type){
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

bool Enemy::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void Enemy::UpdateMovement(){

}

void Enemy::ActorOverlap(Actor otherActor){
    
}


// Base to implement attacks. This should be on the base class and be overriden by the different enemies
bool Enemy::Attack(){
    return true;
}