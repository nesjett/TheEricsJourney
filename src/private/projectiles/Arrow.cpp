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
    MaxBounceCount = 4;
}
void Arrow::Init(){
    debug = true;
    game *gi = game::Instance();
    creationTime = gi->getTime();
    //movementSpeed = 0.65;
    movementSpeed = 0.5;
    damage = 20;

    texture_file = "./resources/projectiles/arrow.png";
    if(sprite){
        delete sprite;
    }
    sprite = new SSprite(texture_file);
    
    sprite->setOrigin(397/2, 74/2);
    sprite->setTextureRect( 0, 0 , 397, 74 );
    sprite->setScale(0.16, 0.17);
    sprite->setBounds(0.5);


    Animation *tmpA;

    //IDLE
    tmpA = new Animation(sprite->getSpriteR(), 1500, true);
    Animations.insert({"IDLE", tmpA});
    tmpA->addFrame({sf::IntRect(0,0, 397,74)});
    
}

void Arrow::Update(float delta){
    float x, y;
    
    x = getActorLocation().x + movementSpeed*direction.x*delta;
    y = getActorLocation().y + movementSpeed*direction.y*delta;

    Actor *collide = DirectionPrecheck(Vector2f(x, y), worldstatic);

    if(collide) { // Update direction for next loop to take effect. THis loop we maintain the movement to avoid projectile to bounce away from the wall.
        if (abs(direction.x) < abs(direction.y)) { // moving vertically
            if(abs(collide->getActorLocation().x - this->getActorLocation().x) < abs(collide->getActorLocation().y - this->getActorLocation().y)) { // object is bottom
                this->setDirection(Vector2f(direction.x, -direction.y));
            } else {
                this->setDirection(Vector2f(-direction.x, direction.y));// object is top
            }
        } else { // moving horizontally
                if(abs(collide->getActorLocation().x - this->getActorLocation().x) > abs(collide->getActorLocation().y - this->getActorLocation().y) ) { // object is right
                this->setDirection(Vector2f(-direction.x, direction.y));
            } else {
                this->setDirection(Vector2f(direction.x, -direction.y));// object is left
            }     
        }

        BounceCount++;
    }

    UpdateMovement(Vector2f(x,y));
    

    // std::atan2 uses y, x signs' for quadrant signification, unlike std::atan
    // SFML's y-axis is flipped: flip our y-component
    auto angleRads = std::atan2(-direction.y, -direction.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    sprite->setRotation(angleDegs);

    Projectile::Update(delta);

    Engine* eng = Engine::Instance();
    // Delete projectiles that are out of the current view.
    // TODO: Bug: THis is deleting projectiles on top and bottom of map, ask @amador about how view works.
    /*if(!eng->getApp().getViewport(eng->getApp().getView()).contains(getInterpolatedPos().x, getInterpolatedPos().y)) {
        setLifespan(4.f);
    }*/

    
}

void Arrow::Draw(double percent, double delta ) {
    Projectile::Draw(percent, delta);
    if(debug) {
        Engine *eng = Engine::Instance();
        eng->getApp().draw(movementTraceDebug);
    }
}


void Arrow::OnActorOverlap(Actor *otherActor){ // Implement Buncing...? hehehe
    //Projectile::OnActorOverlap(otherActor); 

    if(lastDamaged){
        if (otherActor != lastDamaged && DmgApplied == false && dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == targetFaction ) {
            otherActor->TakeDamage(damage+rand() % 20 + (-10), this, ProjectileName);
            lastDamaged = otherActor;
        }
    }

    if(dynamic_cast<Tile*>(otherActor)){
        if(BounceCount > MaxBounceCount){
            setLifespan(0.f);
            return;
        }

        if(lastCollided) {
            timer.restart();
            lastCollided = otherActor;
        }
    }
    
    /*
    if ( DmgApplied == false && dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == targetFaction ) {
        otherActor->TakeDamage(damage+rand() % 20 + (-10), this, ProjectileName);
        DmgApplied = true;
        setLifespan(0.0);
    } else {
        if(dynamic_cast<Tile*>(otherActor)){
            DmgApplied = true;
            setLifespan(0.0);
        }
    }*/
}


Actor* Arrow::DirectionPrecheck(Vector2f loc, ObjectType type) {
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


Arrow::~Arrow(){
    //delete sprite;
}


