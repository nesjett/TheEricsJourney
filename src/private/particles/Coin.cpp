#include "../../public/particles/Coin.h"


Coin::Coin(Vector2f Loc) : Cascade(Loc) {
    this->LoadTexture("./resources/particles/gemBlue.png");
    this->SetLifetime(-1);

    this->setOrigin(64/2, 64/2);
    this->setTextureRect( 0, 0 , 64, 64 );
    this->setScale(1.f, 1.f);

    //this->setBounds(0.5);

    //IDLE
    Anim = new Animation(this->getSpriteR(), 2000, false);
    Anim->addFrame({sf::IntRect(0,0, 64,64)});


}

Coin::~Coin(){

}



