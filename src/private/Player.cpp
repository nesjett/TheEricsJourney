#include "../public/Player.h"

Player::Player(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file2 = "./resources/sprites.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(0.f, 0.f);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 5.0f;

    Init();

}

void Player::Init(){
    sprite = new SSprite(texture_file2);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect( 0, 0 ,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}
void Player::Draw(double percent, double delta ){
   Actor::Draw(percent, delta); 
}

void Player::Update(float delta){
    bool estado=IsAlive();
    if(estado==true){
        Pawn::Update( delta);
    }
    
}
void Player::TakeDamage(float damage, string damage_type){
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

bool Player::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void Player::Movimiento(sf::Vector2f pos){
    direction = pos;
}
void Player::setDirection(float x, float y){
    direction.x = x;
    direction.y = y;
}
sf::Vector2f Player::getDirection(){
    return direction;
}


void Player::UpdateMovement(){

}

void Player::ActorOverlap(Actor otherActor){

}


// Base to implement attacks. This should be on the base class and be overriden by the different enemies
bool Player::Attack(){
    return true;
}