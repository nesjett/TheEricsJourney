#include "../../public/particles/PlayerHit.h"

#include <game.h>

PlayerHit::PlayerHit(Vector2f Loc) : Cascade(Loc) {
    this->LoadTexture("./resources/hit-sparkle.png");
    this->SetLifetime(2000);

    this->setOrigin(32/2, 32/2);
    this->setTextureRect( 0, 5 , 32, 32 );
    this->setScale(1.5, 1.5);

    this->setBounds(0.5);

    //IDLE
    Anim = new Animation(this->getSpriteR(), 2000, false);
    Anim->addFrame({sf::IntRect(0,0, 32,32)});
    Anim->addFrame({sf::IntRect(32,0, 32,32)});
    Anim->addFrame({sf::IntRect(64,0, 32,32)});

    Anim->addFrame({sf::IntRect(0,32, 32,32)});
    Anim->addFrame({sf::IntRect(32,32, 32,32)});
    Anim->addFrame({sf::IntRect(64,32, 32,32)});

    Anim->addFrame({sf::IntRect(0,64, 32,32)});
    Anim->addFrame({sf::IntRect(32,64, 32,32)});

}

PlayerHit::~PlayerHit(){

}



