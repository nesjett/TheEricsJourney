#include "../../public/projectiles/Almendra.h"

#include "../../public/game.h"
#include "../../public/AudioManager.h"


Almendra::Almendra() : Projectile(){ // Use this to call to parent's contructor first
    Init();
}
Almendra::Almendra(sf::Vector2f dir, sf::Vector2f pos) : Projectile(){
    Init();
    direction = dir;
    setActorLocation(pos); 
    activeAnim = Animations.find("IDLE")->second;
}
void Almendra::Init(){
    movementSpeed = 0.23;
    damage = 20;
    debug = true;

    texture_file = "./resources/projectiles/almendra.png";
    if(sprite){
        delete sprite;
    }
    sprite = new SSprite(texture_file);
    
    sprite->setOrigin(512/2, 197/2);
    sprite->setTextureRect( 0, 5 , 512, 197 );
    sprite->setScale(0.35, 0.35);

    sprite->setBounds(0.35);


    Animation *tmpA;

    //IDLE
    tmpA = new Animation(sprite->getSpriteR(), 4100, true);
    Animations.insert({"IDLE", tmpA});
    tmpA->addFrame({sf::IntRect(0,0, 512,197)});
    tmpA->addFrame({sf::IntRect(512,0, 512,197)});
    tmpA->addFrame({sf::IntRect(1024,0, 512,197)});
    tmpA->addFrame({sf::IntRect(0,197, 512,197)});
    tmpA->addFrame({sf::IntRect(512,197, 512,197)});
    tmpA->addFrame({sf::IntRect(1024,197, 512,197)});
    
}

void Almendra::Update(float delta){ // TODO: MOve rotation calculation out of Update(), it only needs to update once for this projectiles.
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

void Almendra::OnActorOverlap(Actor *otherActor) {

    if(dynamic_cast<Tile*>(otherActor)){
        game *gi = game::Instance();
        gi->SpawnEmitterAtLocation(3, getActorLocation(), Vector2f(0.f,0.f));
        AudioManager::getInstance()->PlaySound2D("./resources/audio/hit.ogg");
    }
    Projectile::OnActorOverlap(otherActor);
    
}

Almendra::~Almendra(){
    //delete sprite;
}


