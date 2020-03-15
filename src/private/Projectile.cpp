#include "../public/Projectile.h"



Projectile::Projectile() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Projectile spawned..." << std::endl;  
    
    texture_file = "./resources/sprites.png";
    direction = Vector2f(1.f, 1.f); // Initially It has no direction
    movementSpeed = 0.2;
    //PrepareSprite();
    Init();
}
void Projectile::Init(){
    sprite = new SSprite(texture_file);
    std::cout << "Terminamos INIT()" << std::endl;
}

void Projectile::Update(float delta){
    //std::cout << "Iniciamos UPDATE(): " << delta << std::endl;
    UpdateMovement(delta);
}


void Projectile::UpdateMovement(float delta){
    float x = movementSpeed*direction.x*delta;
    float y = movementSpeed*direction.y*delta;
    x = getActorLocation().x + x;
    y = getActorLocation().y + y;
    if( x > 700) { // reset position for testing
        setActorLocation(Vector2f(0,0), true);
    } else {
        setActorLocation(Vector2f(x,y));
    }

    // std::atan2 uses y, x signs' for quadrant signification, unlike std::atan
    // SFML's y-axis is flipped: flip our y-component
    auto angleRads = std::atan2(direction.y, -direction.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    sprite->setRotation(angleDegs);
}

void Projectile::Draw(float percent){
    sprite->Draw(location, location_prev, percent);
}

Projectile::~Projectile(){
    //delete sprite;
}


