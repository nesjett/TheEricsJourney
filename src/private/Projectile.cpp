#include "../public/Projectile.h"

#include <Tile.h>


Projectile::Projectile() : Actor(){ // Use this to call to parent's contructor first
    //std::cout << "Projectile spawned..." << std::endl;  
    
    texture_file = "./resources/sprites.png";
    direction = Vector2f(1.f, 1.f); // Initially It has no direction
    movementSpeed = 0.2;
    damage = 20;
    ProjectileName = "PROJECTILE_BASE";

    debug = false;
    debug_coords = false;

    targetFaction = allie;
    oType = projectile; // Set the collision channel
    Init();
}
Projectile::Projectile(sf::Vector2f dir, sf::Vector2f pos) : Actor(){
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
    /*sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect( 0, 0 ,75,75 );*/
    //std::cout << "Terminamos INIT()" << std::endl;
}

void Projectile::Update(float delta){
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
        otherActor->TakeDamage(damage, this, ProjectileName);
        DmgApplied = true;
        setLifespan(0.0);
    } else {
        if(dynamic_cast<Tile*>(otherActor)){
            DmgApplied = true;
            setLifespan(0.0);
        }
    }
}

Projectile::~Projectile(){
    delete activeAnim;
    Animations.erase(Animations.begin(), Animations.end());
}


