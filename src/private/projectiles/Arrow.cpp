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
    debug = false;
    game *gi = game::Instance();
    creationTime = gi->getTime();
    //movementSpeed = 0.65;
    movementSpeed = 0.5;
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

    Engine* eng = Engine::Instance();
    // Delete projectiles that are out of the current view.
    // TODO: Bug: THis is deleting projectiles on top and bottom of map, ask @amador about how view works.
    if(!eng->getApp().getViewport(eng->getApp().getView()).contains(getInterpolatedPos().x, getInterpolatedPos().y)) {
        setLifespan(4.f);
    }

    /*if(timer.getElapsedTime().asMilliseconds() > 1500) {
        lastCollided = nullptr;
    }*/
    direction = direction;
    Vector2f finalPos = Vector2f(direction.x*80,direction.y*80);
    lastCollided = DirectionPrecheck(getInterpolatedPos(), finalPos, worldstatic);
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
            otherActor->TakeDamage(damage, this, ProjectileName);
            lastDamaged = otherActor;
        }
    }

    if(dynamic_cast<Tile*>(otherActor)){
        Engine *eng = Engine::Instance();

        Vector2f DirToOther = otherActor->getActorLocation() - getInterpolatedPos();
        float aux=sqrt(pow(DirToOther.x, 2)+pow(DirToOther.y, 2));
        DirToOther=Vector2f(DirToOther.x/aux,DirToOther.y/aux); // normalized direction to other actor

        //Vector2f VerticalDown = Vector2f(0.f, 1.f);

        float dot = direction.x * DirToOther.x + direction.y * DirToOther.y; // dot product 
        //float det = direction.x * VerticalDown.x - direction.y * VerticalDown.y;
        if(lastCollided /*|| lastCollided != otherActor*/) {
            timer.restart();
            
        
            //if(dot > 0.5 || dot < -0.5) {
                lastCollided = otherActor;
               
                //this->setDirection(Vector2f(-direction.x, direction.y));
                 
            //}

            // which side did it happen on?
            if (abs(direction.x) < abs(direction.y)) {
                if (direction.y > 0) { // bottom
                    this->setDirection(Vector2f(direction.x, -direction.y));
                    std::cout << "ARROW COLLIDE " << creationTime << " bottom" << std::endl;
                } else { // top
                    std::cout << "ARROW COLLIDE " << creationTime << " top top" << std::endl;
                    this->setDirection(Vector2f(direction.x, -direction.y));
                }
            } else {
                if (direction.x > 0) { // right
                    this->setDirection(Vector2f(-direction.x, direction.y));
                    std::cout << "ARROW COLLIDE " << creationTime << " right" << std::endl;
                } else { // top
                    this->setDirection(Vector2f(direction.x, -direction.y));
                    std::cout << "ARROW COLLIDE " << creationTime << " top" << std::endl;
                }
            }
        }
    }
}


Actor* Arrow::DirectionPrecheck(Vector2f InitialLocation, Vector2f FinalLocation, ObjectType type) {
    game *gi = game::Instance();
    FloatRect trace = FloatRect(Vector2f(InitialLocation.x, InitialLocation.y), 
        Vector2f(FinalLocation.x,FinalLocation.y));

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


