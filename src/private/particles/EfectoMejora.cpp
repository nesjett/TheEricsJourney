#include "../../public/particles/EfectoMejora.h"

#include <game.h>

EfectoMejora::EfectoMejora(Vector2f Loc) : Cascade(Loc) {
    this->LoadTexture("./resources/mejora.png");
    this->SetLifetime(2000);

    this->setOrigin(64/2, 64/2);
    this->setTextureRect( 0, 5 , 64, 64 );
    this->setScale(1.5, 1.5);

    this->setBounds(0.5);

    //IDLE
    Anim = new Animation(this->getSpriteR(), 2000, false);
    Anim->addFrame({sf::IntRect(0,0, 64,64)});
    Anim->addFrame({sf::IntRect(0,64, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*2, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*3, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*4, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*5, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*6, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*7, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*8, 64,64)});
    Anim->addFrame({sf::IntRect(0,64*9, 64,64)});
    
    

}

EfectoMejora::~EfectoMejora(){

}



