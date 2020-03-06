#include "../public/Pawn.h"

#include <iostream>

Pawn::Pawn() {
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    location = Vector2f(0.f, 0.f); // INit location to world center
    direction = Vector2f(0.f, 0.f);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 2.0f;
    
    bala.setFillColor(sf::Color::Red);

    PrepareSprite();

    Update(0.f);
}

void Pawn::PrepareSprite(){
    sf::Texture tex;
    if (!tex.loadFromFile(texture_file)) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    //Y creo el spritesheet a partir de la imagen anterior
    sprite.setTexture(tex);

    //Le pongo el centroide donde corresponde
    sprite.setOrigin(75 / 2, 75 / 2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(120, 240);

    //Escala por defecto
    sprite.setScale(1, 1);
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

    direction.x = r;
    direction.y = d;

    sprite.setPosition(r, d);
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

Pawn::~Pawn(){

}