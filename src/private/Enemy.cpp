#include "../public/Enemy.h"
#include "../public/AudioManager.h"

Enemy::Enemy() : Pawn(){ // Use this to call to parent's contructor first

}

void Enemy::Update(float delta){
    //std::cout << "Iniciamos UPDATE()" << std::endl;

}

void Enemy::TakeDamage(float damage, Actor* dmgCauser, string damage_type){
    std::cout << "Damage taken!" << std::endl; 
    if(health_Current > 0){ // Only apply damage if the enemy is alive.
        health_Current-=damage;
        if(IsAlive() == false){
            Die();
            AudioManager::getInstance()->play_enemy1_death();
        } else {
            ApplyHitEffects(damage_type); // Apply hit effects
        }
        AudioManager::getInstance()->play_enemy1_takedamage();
    }
}

bool Enemy::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void Enemy::OnActorOverlap(Actor *otherActor){

}


// Base to implement attacks. This should be on the base class and be overriden by the different enemies
bool Enemy::Attack(){
    return true;
}