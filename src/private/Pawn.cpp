#include "../public/Pawn.h"


Pawn::Pawn() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    direction = Vector2f(0.f, 0.f); // Initially It has no direction

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 2.0f;
    
    bala.setFillColor(sf::Color::Red);

    PrepareSprite();
}

void Pawn::PrepareSprite(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75 / 2, 75 / 2);
    sprite->setTextureRect(0 * 75, 0 * 75, 75, 75);
}


void Pawn::Update(float delta){
    std::cout << "Iniciamos UPDATE()" << std::endl;
    /*if(cInterp.getElapsedTime().asMilliseconds() >= 1000/15){
        UpdateMovement();
        cInterp.restart();
    }*/

    /*game& gi = *game::Instance();
    std::cout << gi.getWindow().isOpen() << std::endl;
    while (gi.getWindow().isOpen()) {
        gi.getWindow().draw(bala);
        //std::cout << "PINTANDO!!" << std::endl;
    }*/
}

// TODO: Use delta time and interpolation
void Pawn::UpdateMovement(){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float d = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    std::cout << "Movement dir: " << r << ":" << d << std::endl; 

    //direction.x = r;
    //direction.y = d;

    setActorLocation(Vector2f(r, d));
}

void Pawn::Draw(float percent){
    sprite->Draw(location, location_prev, percent);
}


void Pawn::TakeDamage(float damage, string damage_type){
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

bool Pawn::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void Pawn::Die(){
    std::cout << "Enemy died!" << std::endl; 
}

void Pawn::ApplyHitEffects(string damage_type){
    std::cout << "Applying effect:" << damage_type << std::endl; 
}

// Base to implement attacks. This should be on the base class and be overriden by the different enemies
bool Pawn::Attack(){
    return true;
}

