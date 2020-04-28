#include "../public/Projectile.h"



Projectile::Projectile() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Projectile spawned..." << std::endl;  
    
    texture_file = "./resources/sprites.png";
    direction = Vector2f(1.f, 1.f); // Initially It has no direction
    movementSpeed = 0.2;
    damage = 20;

    targetFaction = allie;
    oType = projectile; // Set the collision channel
    Init();
}
Projectile::Projectile(sf::Vector2f dir, sf::Vector2f pos){
    std::cout << "Projectile spawned..." << std::endl;  
    
    texture_file = "./resources/sprites.png";
    // Initially It has no direction
    movementSpeed = 0.2;
    damage = 20;
    direction=Vector2f(1.0,1.0);
    oType = projectile; // Set the collision channel
    
    Init();
    direction = dir;
    setActorLocation(pos); 
}
void Projectile::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect( 0, 0 ,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}

void Projectile::Update(float delta){
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

void Projectile::Draw(double percent, double delta ){
   Actor::Draw(percent, delta); // Debugging
   //sprite->Draw(getActorLocation(), getActorLastLocation(), percent);
}

void Projectile::TakeDamage(float damage, Actor* dmgCauser, string damage_type){

}

void Projectile::OnActorOverlap(Actor *otherActor){
    //otherActor.TakeDamage(damage, "default");
    if ( dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == allie ) { // allie = player related things
        otherActor->TakeDamage(damage, this, "PROJECTILE_X");
    }
}

Projectile::~Projectile(){
    //delete sprite;
}


