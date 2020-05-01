#include "../../public/particles/Fireball_Explosion.h"

#include <game.h>

Fireball_Explosion::Fireball_Explosion(Vector2f Loc) : Cascade(Loc) {
    this->LoadTexture("./resources/projectiles/fireball-explosion.png");
    this->SetLifetime(2000);

    this->setOrigin(120/2, 172/2);
    this->setTextureRect( 0, 5 , 120, 172 );
    this->setScale(0.35, 0.35);

    this->setBounds(0.5);

    //IDLE
    Anim = new Animation(this->getSpriteR(), 2000, true);
    Anim->addFrame({sf::IntRect(0,0, 120,172)});
    Anim->addFrame({sf::IntRect(120,0, 120,172)});
    Anim->addFrame({sf::IntRect(0,172, 120,172)});
    Anim->addFrame({sf::IntRect(120,172, 120,172)});
    Anim->addFrame({sf::IntRect(0,344, 120,172)});
    Anim->addFrame({sf::IntRect(120,344, 120,172)});
}

Fireball_Explosion::~Fireball_Explosion(){

}



