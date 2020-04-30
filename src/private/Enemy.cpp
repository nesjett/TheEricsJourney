#include "../public/Enemy.h"
#include "../public/AudioManager.h"

Enemy::Enemy() : Pawn(){ // Use this to call to parent's contructor first
    Targetted = false;
    PrepareMarker();
}

void Enemy::PrepareMarker(){
    TargetMarker = new SSprite("./resources/target.png");
    TargetMarker->setScale(0.55,0.55); // 0.4 is the marker texture scale
}

void Enemy::Update(float delta){
    //std::cout << "Iniciamos UPDATE()" << std::endl;
    Pawn::Update(delta);
    
}

void Enemy::Draw(double percent, double delta ){
    if(Targetted) {
        float offsetx = TargetMarker->getSpriteR().getLocalBounds().width*0.55/2; // 0.4 is the marker texture scale
        float offsety = 20; // 0.4 is the marker texture scale
        TargetMarker->setPosition(this->getInterpolatedPos().x-offsetx, this->getInterpolatedPos().y-offsety);
        TargetMarker->Draw();
    }

    Pawn::Draw(percent, delta);
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

void Enemy::ToggleTarget(bool Active){
    Targetted = Active;
}