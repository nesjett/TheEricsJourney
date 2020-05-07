#include "../../public/traps/Saw.h"

#include <game.h>

Saw::Saw(Vector2f Loc, float Length) : Trap(){ // Use this to call to parent's contructor first
    texture_file = "./resources/traps/saw/saw.png";

    damage_factor = 2.f;
    oType = worlddynamic;
    initialLocation = Loc;
    trapLength = Length;
    setActorLocation(Loc); // PLace actor somewhere in the map

    movementSpeed = 0.1;
    direction = Vector2f(1.f, 0.0); // we always start going right

    PrepareSprite();
}

void Saw::PrepareSprite(){
    float scale = 0.25;
    float sizeX = 274.0, sizeY = 144.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale(scale,scale); // Set the scale of the sprite.

    sprite->setBounds(0.65);
    
    Animation *tmpA;

    /////////////////// WALK_LEFT
    tmpA = new Animation(sprite->getSpriteR(), 1200, true); // Create animation
    Animations.insert({"ROTATING", tmpA}); // Add to animations map
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(274,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,144,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(274,144,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,288,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(274,288,sizeX,sizeY)});

    activeAnim = Animations.find("ROTATING")->second;

    CreateRail();
}

void Saw::CreateRail() {
    // rail
    float scale = 0.25;
    float sizeX = 74.0, sizeY = 34.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    int nbrSprites = floor(trapLength / (sizeX *scale));

    trapLength = nbrSprites * (sizeX * scale);

    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);

    rail.push_back(make_unique<SSprite>("./resources/traps/saw/left.png"));
    rail.back()->setPosition(initialLocation.x, initialLocation.y);
    rail.back()->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    rail.back()->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    rail.back()->setScale(scale,scale);

    // first and last sprites are the corners so we set them manually, then loop for the body parts
    for(int i = 1; i < nbrSprites-1; i++) {
        rail.push_back(make_unique<SSprite>("./resources/traps/saw/body.png"));
        rail.back()->setPosition(initialLocation.x+(sizeX * scale) * i, initialLocation.y);
        rail.back()->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
        rail.back()->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
        rail.back()->setScale(scale,scale);
    }

    rail.push_back(make_unique<SSprite>("./resources/traps/saw/right.png"));
    rail.back()->setPosition(initialLocation.x+trapLength-(sizeX*scale), initialLocation.y); // we have to deduct the size of the sprite for good positioning
    rail.back()->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    rail.back()->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    rail.back()->setScale(scale,scale);
}

void Saw::Update(float delta){

    
    if(direction.x > 0.f) {
        // we go right, check we arrive to the right poing
        if(getActorLocation().x >= initialLocation.x + trapLength - 74.f*0.25 * 2) { // deduct tile size twice, bug on calculations during rail creation...
            direction.x = -1.f;
        }
    } else {
        // we go left, check we arrive to origin. dir.x == 0.f should not happen
        if(getActorLocation().x <= initialLocation.x + 74.f*0.25) {
            direction.x = 1.f;
        }
    }

    float x = movementSpeed*direction.x*delta;
    x = getActorLocation().x + x;
    float y = getActorLocation().y;

    UpdateMovement( Vector2f (x,y) );

    Trap::Update(delta);
    bool valid = false;
    if(target && timer.getElapsedTime().asSeconds() >= 5) {
        target = nullptr;
    }

}

void Saw::Draw(double percent, double delta ){
    

    // Draw rail first to be under the saw
    for (auto&& sp: rail) { 
        sp->Draw();
    }
    
    Trap::Draw(percent, delta);

    if(activeAnim){
        activeAnim->update(delta);
    }
}

void Saw::OnActorOverlap(Actor *otherActor){
    if ( dynamic_cast<Player*>(otherActor) && dynamic_cast<Player*>(otherActor)->getFaction() == allie ) { // allie = player related things
        target = otherActor;
        target->TakeDamage(damage_factor, this, "TRAP_X");
        timer.restart();
    }
}


