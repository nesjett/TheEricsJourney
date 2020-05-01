#include "../../public/traps/Saw.h"

#include <game.h>

Saw::Saw(Vector2f Loc, float Length) : Trap(){ // Use this to call to parent's contructor first
    texture_file = "./resources/traps/saw/saw.png";

    damage_factor = 2.f;
    oType = worlddynamic;
    setActorLocation(Loc); // PLace actor somewhere in the map



    PrepareSprite();
}

void Saw::PrepareSprite(){
    float scale = 0.25;
    float sizeX = 274.0, sizeY = 144.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale(scale,scale); // Set the scale of the sprite.
    
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
}

void Saw::Update(float delta){
   Trap::Update(delta);
   bool valid = false;
   if(target && timer.getElapsedTime().asSeconds() >= 5) {
        target = nullptr;
   }

}

void Saw::Draw(double percent, double delta ){
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


