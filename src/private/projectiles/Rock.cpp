#include "../../public/projectiles/Rock.h"



Rock::Rock() : Projectile(){ // Use this to call to parent's contructor first
    Init();
}
Rock::Rock(sf::Vector2f dir, sf::Vector2f pos) : Projectile(dir, pos){
    Init();
    
    activeAnim = Animations.find("IDLE")->second;
}
void Rock::Init(){
    movementSpeed = 0.1;
    damage = 20;

    texture_file = "./resources/projectiles/rock.png";
    if(sprite){
        delete sprite;
    }
    sprite = new SSprite(texture_file);
    
    sprite->setOrigin(400/2, 400/2);
    sprite->setTextureRect( 0, 5 , 400, 400 );
    sprite->setScale(0.1,0.1);

    sprite->setBounds(0.5);


    Animation *tmpA;

    //IDLE
    tmpA = new Animation(sprite->getSpriteR(), 1600, true);
    Animations.insert({"IDLE", tmpA});
    tmpA->addFrame({sf::IntRect(0,0, 400,400)});
    tmpA->addFrame({sf::IntRect(0,400, 394,394)});
    tmpA->addFrame({sf::IntRect(0,794, 394,394)});
    tmpA->addFrame({sf::IntRect(0,1188, 394,394)});
    
}

void Rock::Update(float delta){
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


Rock::~Rock(){
    //delete sprite;
}


