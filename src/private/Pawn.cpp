#include "../public/Pawn.h"


Pawn::Pawn() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/zombie_male_idle.png";

    direction = Vector2f(0.f, 0.f); // Initially It has no direction

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 2.0f;

    //faction = enemy; // By default we set the faction to enemy, just for easy of use
    
    bala.setFillColor(sf::Color::Red);

    PrepareSprite();
}

void Pawn::PrepareSprite(){
    sprite = new SSprite(texture_file);
    //sprite->setOrigin(450 / 2, 550 / 2);
    sprite->setOrigin(0, 0);
    sprite->setScale(0.4,0.4);
    //sprite->setTextureRect(0 * 75, 0 * 75, 75, 75);
    double playrate = 5000.0;
    int sizeX = 430, sizeY = 500;

    animation = new Animation(sprite->getSpriteR());
    animation->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(430,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(860,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(1290,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(1720,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(2150,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(2580,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(3010,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(3440,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(3870,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(4300,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(4730,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(5160,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(5590,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(6020,0,sizeX,sizeY), playrate});
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

void Pawn::Draw(double percent, double delta ){
    animation->update(delta);
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

