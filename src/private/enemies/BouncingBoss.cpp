#include "../../public/enemies/BouncingBoss.h"

#include <AudioManager.h>

BouncingBoss::BouncingBoss(): Enemy(){
    NbrChildren = 2;
    health_MAX = 800.0f;
    this->SetDirection(Vector2f(0.5, 0.5));
    SpriteScale = 1;

    Init();
    PrepareSprite();
}

BouncingBoss::BouncingBoss(Vector2f Dir, int Childrens, float Scale, float MaxHealth): Enemy(){ // Use this to call to parent's contructor first
    NbrChildren = Childrens;
    health_MAX = MaxHealth;
    this->SetDirection(Dir);
    SpriteScale = Scale;

    Init();
    PrepareSprite();
}

void BouncingBoss::Init(){
    debug = true;
    setActorLocation(Vector2f(100.f, 100.f));
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.2f;
}

void BouncingBoss::PrepareSprite(){
    texture_file = "./resources/enemies/BouncingBoss.png";

    float sizeX = 540.0, sizeY = 459.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale( 0.25*SpriteScale,0.25*SpriteScale );
    sprite->setBounds(0.8);
    
    Animation *tmpA;

    tmpA = new Animation(sprite->getSpriteR(),3000, true);
    Animations.insert({"MOVING", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,459,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(), 750, true);
    Animations.insert({"HIT", tmpA});
    tmpA->addFrame({sf::IntRect(0,918,sizeX,sizeY)});
}

void BouncingBoss::Update(float delta){
    //Enemy::Update(delta); // Override enemy and pawn movements

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
                // CHange direction
                float newX = 0;
                float newY = 0;
                /* The result will be -1 if the target is directly behind, +1 if directly ahead and zero if it is side-on to the 
                NPC in any direction (including above, below, etc). The value is actually the cosine of the angle between the two 
                vectors. You can check if it is greater than zero to see if the target is basically ahead of the NPC. However, you 
                can create a narrower field of view by using the cosine of the angle you want. For example, a value of 0.5 means the 
                target can't be more than 30º either side of head-on to be detected. */
                Vector2f DirToOther = collide->getActorLocation() - getInterpolatedPos();
                float aux=sqrt(pow(DirToOther.x, 2)+pow(DirToOther.y, 2));
                DirToOther=Vector2f(DirToOther.x/aux,DirToOther.y/aux); // normalized direction to other actor

                float dot = direction.x * DirToOther.x + direction.y * DirToOther.y; // dot product 
            }
        } else {
            // Change direction
            float newX = 0;
            float newY = 0;
            /* The result will be -1 if the target is directly behind, +1 if directly ahead and zero if it is side-on to the 
            NPC in any direction (including above, below, etc). The value is actually the cosine of the angle between the two 
            vectors. You can check if it is greater than zero to see if the target is basically ahead of the NPC. However, you 
            can create a narrower field of view by using the cosine of the angle you want. For example, a value of 0.5 means the 
            target can't be more than 30º either side of head-on to be detected. */
            /*Vector2f DirToOther = collide->getActorLocation() - getInterpolatedPos();
            float aux=sqrt(pow(DirToOther.x, 2)+pow(DirToOther.y, 2));
            DirToOther=Vector2f(DirToOther.x/aux,DirToOther.y/aux); // normalized direction to other actor

            float dot = direction.x * DirToOther.x + direction.y * DirToOther.y; // dot product 
            */
            if (abs(direction.x) < abs(direction.y)) { // moving vertically
                if(abs(collide->getActorLocation().x - this->getActorLocation().x) < abs(collide->getActorLocation().y - this->getActorLocation().y)) { // object is bottom
                    this->SetDirection(Vector2f(direction.x, -direction.y));
                } else {
                    this->SetDirection(Vector2f(-direction.x, -direction.y));// object is top
                }
            } else { // moving horizontally
                 if(abs(collide->getActorLocation().x - this->getActorLocation().x) > abs(collide->getActorLocation().y - this->getActorLocation().y) ) { // object is right
                    this->SetDirection(Vector2f(-direction.x, direction.y));
                } else {
                    this->SetDirection(Vector2f(direction.x, -direction.y));// object is left
                }
                    
                
            }

            setActorLocation( this->getActorLastLocation() ); // Move to last valid location, prevent intersecting with the collider actor
        }
    }

    Actor::Update(delta);
}

void BouncingBoss::Draw(double percent, double delta ){
    long cTime = InternalClock.getElapsedTime().asMilliseconds();

    /* Update status based on times */
    if(DmgAnimationEndTime != -1 && cTime >= DmgAnimationEndTime) {
        DmgAnimationEndTime = -1;
    }
    if(DmgCooldownEndTime != -1 && cTime >= DmgCooldownEndTime) {
        DmgCooldownEndTime = -1;
    }
    
    /* Apply special class animations */
    if(DmgAnimationEndTime == -1) { 
        activeAnim=Animations.find("MOVING")->second;
    } else { // draw hit animation for some time until clock decides to stop it
        activeAnim=Animations.find("HIT")->second;
    }

    /* Call to parents behaviour, always */
    Enemy::Draw(percent, delta);
}


void BouncingBoss::TakeDamage(float damage, Actor* dmgCauser, string damage_type) {
   DmgAnimationEndTime = InternalClock.getElapsedTime().asMilliseconds() + TimeBetweenAttacks; // Set playing this animation until some time in the future
   Enemy::TakeDamage(damage, dmgCauser, damage_type); // Parents process damage
}

void BouncingBoss::OnActorOverlap(Actor *otherActor){
    // Apply damage only to Pawn actors with faction "allie"
    if ( DmgCooldownEndTime == -1 && dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == allie ) {
        otherActor->TakeDamage(damage_Base, this, "BOUNCING_BOSS");
        DmgCooldownEndTime = InternalClock.getElapsedTime().asMilliseconds() + TimeDmgAnimation; // Set next available attack somewhere in the future
    }
}

void BouncingBoss::Die() {

    if(NbrChildren > 0) { // spawn children
        game *gi = game::Instance();
        // Vector2f Dir, int Childrens, float Scale, float MaxHealth
        BouncingBoss *tmp = new BouncingBoss(GetDirection(), NbrChildren, 0.85, 200.f);
        tmp->setActorLocation(getActorLocation());
        gi->Almacenaenemy(tmp);
        tmp = new BouncingBoss(GetDirection(), NbrChildren, 0.85, 200.f);
        tmp->setActorLocation(getActorLocation());
        gi->Almacenaenemy(tmp);
    }

    setLifespan(0.1); // ENsure everything spawns before destroying
}

void BouncingBoss::RandomDeviateDirectionInRange(Vector2f Direction, float Debiation) {

}

BouncingBoss::~BouncingBoss() {

}