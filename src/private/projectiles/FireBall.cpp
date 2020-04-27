#include "../../public/projectiles/FireBall.h"



FireBall::FireBall() : Projectile(){ // Use this to call to parent's contructor first
    texture_file = "./resources/projectiles/fireball-512.png";
    movementSpeed = 0.1;
    damage = 20;

    Init();
}
FireBall::FireBall(sf::Vector2f dir, sf::Vector2f pos){
    std::cout << "FireBall spawned..." << std::endl;  
    
    texture_file = "./resources/projectiles/fireball-512.png";
    // Initially It has no direction
    movementSpeed = 0.1;
    damage = 20;
    
    Init();
    direction = dir;
    setActorLocation(pos); 
}
void FireBall::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect( 0, 0 ,75,75 );
}

void FireBall::Update(float delta){
    float x = movementSpeed*direction.x*delta;
    float y = movementSpeed*direction.y*delta;
    x = getActorLocation().x + x;
    y = getActorLocation().y + y;
    
    UpdateMovement(Vector2f(x,y));
    

    // std::atan2 uses y, x signs' for quadrant signification, unlike std::atan
    // SFML's y-axis is flipped: flip our y-component
    auto angleRads = std::atan2(direction.y, -direction.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    sprite->setRotation(angleDegs);
}


void FireBall::OnActorOverlap(Actor *otherActor){
    //otherActor.TakeDamage(damage, "default");
    if ( dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == allie ) { // allie = player related things
        otherActor->TakeDamage(damage, this, "PROJECTILE_X");
    }
}

FireBall::~FireBall(){
    //delete sprite;
}


