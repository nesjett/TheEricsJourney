#include "../public/Door.h"
#include "../public/Pawn.h"
#include "../public/game.h"
#include "../public/Hud.h"
#include "../public/AudioManager.h"



Door::Door(Vector2f position, bool esPuertaSuperior) : Actor(){ 
    texture_file = "./resources/maps/tiles/doorspritesheet2.png";
    abierta = false;
    superior = esPuertaSuperior;
    PrepareSprite();
    setActorLocation(position);
    oType = worldstatic;
}

void Door::openDoor()
{
    abierta = true;
    oType = door; //Se puede colisionar
    AudioManager::getInstance()->PlaySound2D("./resources/audio/door_open.ogg");
}

void Door::PrepareSprite(){
    float sizeX, sizeY;
    sizeX = 145.f;
    sizeY = 166.f;
    sprite = new SSprite(texture_file);
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); 
    sprite->setOrigin(0, sizeY); 
    sprite->setScale((100/145.f),(100/166.f)); 

    Animation* tmpA = new Animation(sprite->getSpriteR(), 1200); 
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(145,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(290,0,153.f,sizeY)});
    activeAnim = tmpA;
}

void Door::Update(float delta){
    Actor::Update(delta);
}
void Door::Draw(double percent, double delta)
{
    Actor::Draw(percent, delta);

    if(activeAnim && abierta == true){
        activeAnim->update(delta);
    }
}
void Door::OnActorOverlap(Actor *otherActor){

}