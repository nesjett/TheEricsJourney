#include "../public/Projectile.h"



Projectile::Projectile() : Actor(){ // Use this to call to parent's contructor first
    //std::cout << "Projectile spawned..." << std::endl;  
    
    texture_file = "./resources/sprites.png";
    direction = Vector2f(1.f, 1.f); // Initially It has no direction
    movementSpeed = 0.2;
    damage = 20;
    ProjectileName = "PROJECTILE_BASE";

    targetFaction = allie;
    oType = projectile; // Set the collision channel
    Init();
}
Projectile::Projectile(sf::Vector2f dir, sf::Vector2f pos){
    //std::cout << "Projectile spawned..." << std::endl;  
    
    texture_file = "./resources/sprites.png";
    // Initially It has no direction
    movementSpeed = 0.2;
    damage = 20;
    oType = projectile; // Set the collision channel
    targetFaction = allie;
    ProjectileName = "PROJECTILE_BASE";
    
    Init();
    direction = dir;
    setActorLocation(pos); 
}
void Projectile::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect( 0, 0 ,75,75 );
    //std::cout << "Terminamos INIT()" << std::endl;
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
    //sprite->setRotation(angleDegs);

    Actor::Update(delta);
}

void Projectile::Draw(double percent, double delta ){
   Actor::Draw(percent, delta); // Debugging
   if(activeAnim){
       activeAnim->update(delta);
   }
   //sprite->Draw(getActorLocation(), getActorLastLocation(), percent);
}

void Projectile::TakeDamage(float damage, Actor* dmgCauser, string damage_type){

}

void Projectile::OnActorOverlap(Actor *otherActor){
    //otherActor.TakeDamage(damage, "default");
    if ( DmgApplied == false && dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == targetFaction ) {
        otherActor->TakeDamage(damage, this, "PROJECTILE_X");
        DmgApplied = true;
        setLifespan(0.0);
        bool valid = IsValid();
    }
}

Projectile::~Projectile(){
    delete activeAnim;
    Animations.erase(Animations.begin(), Animations.end());
}


