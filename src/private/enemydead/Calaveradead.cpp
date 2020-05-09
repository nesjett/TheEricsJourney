#include "../../public/enemydead/Calaveradead.h"

#include <game.h>

Calaveradead::Calaveradead(Vector2f Loc) : Cascade(Loc) {

    float sizeX = 828.0, sizeY = 896.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    this->LoadTexture("./resources/enemies/dead/Calaveradead.png");
    this->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    this->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    this->setScale( 0.07,0.07 );
    this->SetLifetime(1500);
    Animation *tmpA;

    tmpA = new Animation(this->getSpriteR(),1500, true);
    tmpA->addFrame({sf::IntRect(0,1016,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,1912,sizeX,sizeY)});
    
}

Calaveradead::~Calaveradead(){

}



