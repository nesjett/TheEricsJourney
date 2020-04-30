#include "../../public/projectiles/Arrow.h"



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
    movementSpeed = 0.45;
    damage = 20;

    texture_file = "./resources/projectiles/fireball-512.png";
    if(sprite){
        delete sprite;
    }
    sprite = new SSprite(texture_file);
    
    sprite->setOrigin(85.33/2, 28/2);
    sprite->setTextureRect( 0, 5 , 85.33, 28 );
    sprite->setBounds(0.5);


    Animation *tmpA;

    //IDLE
    tmpA = new Animation(sprite->getSpriteR(), 1500, true);
    Animations.insert({"IDLE", tmpA});
    tmpA->addFrame({sf::IntRect(0,0, 85.33,33)});
    tmpA->addFrame({sf::IntRect(85.33,0,85.33,33)});
    tmpA->addFrame({sf::IntRect(170.66,0,85.33,33)});
    tmpA->addFrame({sf::IntRect(0,33, 85.33,33)});
    tmpA->addFrame({sf::IntRect(85.33,33,85.33,33)});
    tmpA->addFrame({sf::IntRect(170.66,33,85.33,33)});
    
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



Arrow::~Arrow(){
    //delete sprite;
}


