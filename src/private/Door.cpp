#include "../public/Door.h"
#include "../public/Pawn.h"
#include "../public/game.h"
#include "../public/Hud.h"



Door::Door(Vector2f position, bool esPuertaSuperior) : Actor(){ // Use this to call to parent's contructor first

    texture_file = "./resources/maps/tiles/doorspritesheet.png";
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
}

void Door::PrepareSprite(){
    float sizeX, sizeY;
    sizeX = 145.f;
    sizeY = 166.f;
    sprite = new SSprite(texture_file);
    sprite->setOrigin(0, sizeY); 
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); 
    sprite->setScale(0.6896,0.492); 

    Animation* tmpA = new Animation(sprite->getSpriteR(), 1200); // Create animation
    //Animations.insert({"DOORS", tmpA}); // Add to animations map
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(145,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(290,0,sizeX,sizeY)});

    //activeAnim = Animations.find("DOORS")->second;
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