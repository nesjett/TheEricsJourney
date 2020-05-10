
#include "../../public/projectiles/Arrow.h"
#include <Tile.h>
#include <stdlib.h> 
#include <game.h> 

Arrow::Arrow() : Projectile(){ // Use this to call to parent's contructor first
    targetFaction = enemy;
    Init();
}
Arrow::Arrow(sf::Vector2f dir, sf::Vector2f pos) : Projectile(){
    targetFaction = enemy;
    Init();
    direction = dir;
    setActorLocation(pos); 
    activeAnim = Animations.find("IDLE")->second;
}
void Arrow::Init(){
    game *gi = game::Instance();
    //movementSpeed = 0.65;
    movementSpeed = 0.95;
    damage = 20;

    texture_file = "./resources/projectiles/arrow.png";
    if(sprite){
        delete sprite;
    }
    sprite = new SSprite(texture_file);
    
    sprite->setOrigin(330/2, 74/2);
    sprite->setTextureRect( 0, 0 , 830, 74 );
    sprite->setScale(0.16, 0.17);
    sprite->setBounds(20);


    Animation *tmpA;

    //IDLE
    tmpA = new Animation(sprite->getSpriteR(), 1500, true);
    Animations.insert({"IDLE", tmpA});
    tmpA->addFrame({sf::IntRect(0,0, 830,74)});
    
}

void Arrow::Update(float delta){
    float x = movementSpeed*direction.x*delta;
    float y = movementSpeed*direction.y*delta;
    x = getActorLocation().x + x;
    y = getActorLocation().y + y;
    
    UpdateMovement(Vector2f(x,y));
    

    // std::atan2 uses y, x signs' for quadrant signification, unlike std::atan
    // SFML's y-axis is flipped: flip our y-component
    auto angleRads = std::atan2(-direction.y, -direction.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    sprite->setRotation(angleDegs);

    Projectile::Update(delta); 
}

void Arrow::OnActorOverlap(Actor *otherActor){ // Implement Buncing...? hehehe
    if(dynamic_cast<Tile*>(otherActor)){
        game *gi = game::Instance();
        gi->SpawnEmitterAtLocation(4, getActorLocation(), Vector2f(0.f,0.f));
        AudioManager::getInstance()->PlaySound2D("./resources/audio/hit.ogg");
    }

    Projectile::OnActorOverlap(otherActor);
}



Arrow::~Arrow(){
    //delete sprite;
}


