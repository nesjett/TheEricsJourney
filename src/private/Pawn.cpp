#include "../public/Pawn.h"

#include <game.h>

Pawn::Pawn() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/zombie_male_idle.png";

    direction = Vector2f(0.f, 0.f); // Initially It has no direction

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.1f;

    faction = enemy; // By default we set the faction to enemy, just for easy of use

    oType = pawn; // Set the collision channel

    setActorLocation(Vector2f(250.0, 320.0)); // PLace actor somewhere in the map

    PrepareSprite();
}

void Pawn::PrepareSprite(){
    float scale = 0.4;
    float sizeX = 430.0, sizeY = 519.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale(scale,scale); // Set the scale of the sprite.
    
    double playrate = 1000.0;
    Animation *tmpA;

    /////////////////// WALK_FRONT
    tmpA = new Animation(sprite->getSpriteR(), true); // Create animation
    Animations.insert({"WALK_FRONT", tmpA}); // Add to animations map
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(430,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(860,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1290,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1720,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(2150,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(2580,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(3010,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(3440,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(3870,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(4300,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(4730,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(5160,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(5590,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(6020,0,sizeX,sizeY), playrate});


    /////////////////// WALK_LEFT
    tmpA = new Animation(sprite->getSpriteR(), true); // Create animation
    Animations.insert({"WALK_LEFT", tmpA}); // Add to animations map
    tmpA->addFrame({sf::IntRect(2,59,sizeX,sizeY), 500});
    tmpA->addFrame({sf::IntRect(2,59,sizeX,sizeY), 500});
    tmpA->addFrame({sf::IntRect(40,59,sizeX,sizeY), 500});
    tmpA->addFrame({sf::IntRect(40,59,sizeX,sizeY), 500});
}

void Pawn::Update(float delta){
    //std::cout << "Iniciamos UPDATE()" << std::endl;
    float x = movementSpeed*direction.x*delta;
    float y = movementSpeed*direction.y*delta;
    x = getActorLocation().x + x;
    y = getActorLocation().y + y;

    if( (direction.x != 0.f || direction.y != 0.f)) {
        Actor *collide = DirectionPrecheck(Vector2f(x,y), worldstatic);
        if(!collide) {
            UpdateMovement( Vector2f (x,y) );
        }
    }
}

void Pawn::Draw(double percent, double delta ){
    if(activeAnim) {
        activeAnim->update(delta);
    }
    Actor::Draw(percent, delta); // Use this to debug draw bounding box

    if(debug) {
        Engine *eng = Engine::Instance();
        eng->getApp().draw(movementTraceDebug);
    }
}

void Pawn::OnActorOverlap(Actor *otherActor){
    Engine *eng = Engine::Instance();
    std::cout << "Soy " << eng->getObjectType(getObjectType()) << " y me ha tocado un objeto tipo: " << eng->getObjectType(otherActor->getObjectType()) << std::endl;
    /*if(otherActor->getObjectType() == worldstatic) {
        direction = Vector2f(0.f,0.f);
    }*/
}

Actor* Pawn::DirectionPrecheck(Vector2f loc, ObjectType type) {
    game *gi = game::Instance();
    double traceX = loc.x-getBoundingBox().width/2+5; // Offset box to make it fit the center location.
    double traceY = loc.y-getBoundingBox().height/2+5;
    FloatRect trace = FloatRect(Vector2f(traceX, traceY), Vector2f(getBoundingBox().width-10,getBoundingBox().height-10));
    Actor* collide = gi->boxTraceByObjectType( trace, type );

    if(debug) {
        movementTraceDebug = sf::RectangleShape( Vector2f(trace.width,trace.height) );
        // Show actor pre-movement trace box
        movementTraceDebug.setPosition(trace.left,trace.top);
        movementTraceDebug.setFillColor(sf::Color(0,0,0,0));
        movementTraceDebug.setOutlineThickness(2.f);
        movementTraceDebug.setOutlineColor(sf::Color(0, 200, 200));
    }

    return collide;
}


void Pawn::TakeDamage(float damage, string damage_type){
    std::cout << "Damage taken!" << std::endl; 
    if(health_Current > 0){ // Only apply damage if the enemy is alive.
        health_Current-=damage;
        if(IsAlive() == false){
            Die();
        } else {
            ApplyHitEffects(damage_type); // Apply hit effects
        }
    }
}

bool Pawn::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void Pawn::Die(){
    std::cout << "Enemy died!" << std::endl; 
}

void Pawn::ApplyHitEffects(string damage_type){
    std::cout << "Applying effect:" << damage_type << std::endl; 
}

// Base to implement attacks. This should be on the base class and be overriden by the different enemies
bool Pawn::Attack(){
    return true;
}

