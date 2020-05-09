#include "../public/Tile.h"
#include "../public/Pawn.h"


Tile::Tile(string nombreSprite, float x, float y, float widthSprite, float heightSprite, ObjectType tipo) : Actor(){ 
    width = widthSprite;
    height = heightSprite;
    texture_file = nombreSprite;
    debug_coords = false;
    setActorLocation(Vector2f(y+(width/2),x+(height/2))); //las posiciones en sfml primer y luego x

    PrepareSprite();
}

void Tile::PrepareSprite(){
    float sizeX = width, sizeY = height;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY);
}


void Tile::Update(float delta){
    Actor::Update(delta);
}

void Tile::Draw(double percent, double delta){
    Actor::Draw(percent, delta);
}

void Tile::OnActorOverlap(Actor *otherActor){

}






