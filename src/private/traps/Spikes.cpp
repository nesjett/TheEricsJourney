#include "../../public/traps/Spikes.h"

#include <game.h>

Spikes::Spikes() : Trap(){ // Use this to call to parent's contructor first
    texture_file = "./resources/traps/spikes.png";

    damage_factor = 15.f;
    oType = worlddynamic;
    setActorLocation(Vector2f(0.f, 0.f)); // PLace actor somewhere in the map

    PrepareSprite();
}

void Spikes::PrepareSprite(){
    float scale = 0.35;
    float sizeX = 164.0, sizeY = 160.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale(scale,scale); // Set the scale of the sprite.
    
    Animation *tmpA;

    /////////////////// WALK_LEFT
    tmpA = new Animation(sprite->getSpriteR(), true); // Create animation
    Animations.insert({"WALK_LEFT", tmpA}); // Add to animations map
    tmpA->addFrame({sf::IntRect(2,59,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(2,59,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(40,59,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(40,59,sizeX,sizeY)});
}

void Spikes::Update(float delta){
   Actor::Update(delta);
}

void Spikes::Draw(double percent, double delta ){
    Actor::Draw(percent, delta);
}

void Spikes::OnActorOverlap(Actor *otherActor){
    if ( dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == allie ) { // allie = player related things
        target = otherActor;
    }
}


