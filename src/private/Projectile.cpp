#include "../public/Projectile.h"



Projectile::Projectile() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Projectile spawned..." << std::endl;  
    
    texture_file = "./resources/sprites.png";
    // Initially It has no direction
    movementSpeed = 0.2;
    damage = 20;
    direction=Vector2f(1.0,1.0);
    oType = projectile; // Set the collision channel
    
    Init();
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
    if( x > 700) { // reset position for testing
        setActorLocation(Vector2f(0,0));
    } else {
        UpdateMovement(Vector2f(x,y));
    }

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

void Projectile::TakeDamage(float damage, string damage_type){

}

void Projectile::OnActorOverlap(Actor *otherActor){
    //otherActor.TakeDamage(damage, "default");
}

Projectile::~Projectile(){
    //delete sprite;
}





