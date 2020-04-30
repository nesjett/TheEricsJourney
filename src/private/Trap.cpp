#include <Trap.h>

#include <game.h>

Trap::Trap() : Actor(){ // Use this to call to parent's contructor first
    texture_file = "./resources/traps/spikes.png";

    damage_factor = 0.2;
    oType = worlddynamic;
    setActorLocation(Vector2f(0.f, 0.f)); // PLace actor somewhere in the map
    target = nullptr;

    PrepareSprite();
}

void Trap::PrepareSprite(){
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

void Trap::Update(float delta){
   Actor::Update(delta);

   

}

void Trap::Draw(double percent, double delta ){
    Actor::Draw(percent, delta);
}

void Trap::OnActorOverlap(Actor *otherActor){

}


