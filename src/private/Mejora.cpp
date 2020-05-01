#include <Mejora.h>

//#include <game.h>

Mejora::Mejora(PowerUpType tipo) : Actor(){ // Use this to call to parent's contructor first
    // switch(tipo)
    // {
    //     case health:
    //         texture_file = "./resources/health.png";
    //         break;
    //     case movementspeed:

    //         break;
    // }
    //texture_file = "./resources/powerups/"+to_string(tipo)+".png";
    texture_file = "./resources/Zombies.png";
    
    

    setActorLocation(Vector2f(150.f, 150.f)); // PLace actor somewhere in the map

    PrepareSprite();
}

void Mejora::PrepareSprite(){
    float scale = 0.4;
    float sizeX = 430.0, sizeY = 519.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale(scale,scale); // Set the scale of the sprite.
    oType = powerup;
}

void Mejora::Update(float delta){
   Actor::Update(delta);
}

void Mejora::OnActorOverlap(Actor *otherActor){

}
Mejora::~Mejora() // Destructor
{
 
}