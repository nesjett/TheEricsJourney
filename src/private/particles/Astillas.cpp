#include "../../public/particles/Astillas.h"

#include <game.h>

Astillas::Astillas(Vector2f Loc) : Cascade(Loc) {
    this->LoadTexture("./resources/astillas.png");
    this->SetLifetime(500);

    this->setOrigin(64/2, 64/2);
    this->setTextureRect( 0, 5 , 64, 64 );
    this->setScale(1.f, 1.f);

    this->setBounds(0.5);

    //IDLE
    Anim = new Animation(this->getSpriteR(), 500, true);
    Anim->addFrame({sf::IntRect(0,0, 64,64)});
    Anim->addFrame({sf::IntRect(0,64, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*2, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*3, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*4, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*5, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*6, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*7, 64,64)});

}

Astillas::~Astillas(){

}



