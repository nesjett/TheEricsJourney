#include "../../public/particles/Rockexplosion.h"

#include <game.h>

Rockexplosion::Rockexplosion(Vector2f Loc) : Cascade(Loc) {
    this->LoadTexture("./resources/explosion.png");
    this->SetLifetime(1000);

    this->setOrigin(32/2, 32/2);
    this->setTextureRect( 0, 5 , 32, 32 );
    this->setScale(1.8, 1.8);

    this->setBounds(0.5);

    //IDLE
    Anim = new Animation(this->getSpriteR(), 1000, true);
    Anim->addFrame({sf::IntRect(0,0, 32,32)});
    Anim->addFrame({sf::IntRect(0,32, 32,32)});
    Anim->addFrame({sf::IntRect(0,32*2, 32,32)});
    Anim->addFrame({sf::IntRect(0,32*3, 32,32)});
    Anim->addFrame({sf::IntRect(0,32*4, 32,32)});
    Anim->addFrame({sf::IntRect(0,32*5, 32,32)});
    Anim->addFrame({sf::IntRect(0,32*6, 32,32)});
    Anim->addFrame({sf::IntRect(0,32*7, 32,32)});

}

Rockexplosion::~Rockexplosion(){

}



