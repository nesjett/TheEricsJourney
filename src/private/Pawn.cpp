#include "../public/Pawn.h"

#include <game.h>

Pawn::Pawn() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

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

    if( (direction.x != 0.f || direction.y != 0.f) && IsAlive()) {
        Actor *collide = DirectionPrecheck(Vector2f(x,y), worldstatic);
        if(!collide) {
            collide = DirectionPrecheck(Vector2f(x,y), blocker);
            if(!collide) {
                UpdateMovement( Vector2f (x,y) );
            } else {
                float newX = 0;
                float newY = 0;

                // TODO: Calc other direction to stop direction on that component.
                /*
                * The result will be -1 if the target is directly behind, +1 if directly ahead and zero if it is side-on to the NPC in any direction (including above, below, etc). The value is actually the cosine of the angle between the two vectors. You can check if it is greater than zero to see if the target is basically ahead of the NPC. However, you can create a narrower field of view by using the cosine of the angle you want. For example, a value of 0.5 means the target can't be more than 30º either side of head-on to be detected. 
                */
                Vector2f DirToOther = collide->getActorLocation() - getInterpolatedPos();
                float aux=sqrt(pow(DirToOther.x, 2)+pow(DirToOther.y, 2));
                DirToOther=Vector2f(DirToOther.x/aux,DirToOther.y/aux); // normalized direction to other actor

                float dot = direction.x * DirToOther.x + direction.y * DirToOther.y; // dot product 
                //float det = direction.x * VerticalDown.x - direction.y * VerticalDown.y;


                //UpdateMovement( Vector2f (newX,newY) );
            }
        }
    }

    Actor::Update(delta);
}

void Pawn::SetAnimation(){ //selecciona la animacion del mapa de animaciones dependiendo de la direccion del actor

    auto angleRads = std::atan2(-direction.y, direction.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    if(angleDegs<0){
      angleDegs=angleDegs+360; //los grados van de 0 a 180 y de 0 a -180, sumamos 360 para establecer cuadrantes segun los angulos
    }

    if((angleDegs<22.5 && angleDegs>0) || (angleDegs>=337.5 && angleDegs<360)){
        activeAnim=Animations.find("right")->second;
    }
    if(angleDegs<67.5 && angleDegs>=22.5){
        activeAnim=Animations.find("right")->second;
    }
    if(angleDegs<112.5 && angleDegs>=67.5){
        activeAnim=Animations.find("up")->second;
    }
    if(angleDegs<157.5 && angleDegs>=112.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<202.5 && angleDegs>=157.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<247.5 && angleDegs>=202.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<292.5 && angleDegs>=247.5){
        activeAnim=Animations.find("down")->second;
    }
    if(angleDegs<337.5 && angleDegs>=292.5){
        activeAnim=Animations.find("right")->second;
    }
    if(angleDegs==0){
        activeAnim=Animations.find("stop")->second;
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
    //std::cout << "Soy " << eng->getObjectType(getObjectType()) << " y me ha tocado un objeto tipo: " << eng->getObjectType(otherActor->getObjectType()) << std::endl;
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


void Pawn::TakeDamage(float damage, Actor* dmgCauser, string damage_type){
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
    //std::cout << "Enemy died!" << std::endl; 
    setLifespan(0.0);
}

void Pawn::ApplyHitEffects(string damage_type){
    std::cout << "Applying effect:" << damage_type << std::endl; 
}

// Base to implement attacks. This should be on the base class and be overriden by the different enemies
bool Pawn::Attack(){
    return true;
}

