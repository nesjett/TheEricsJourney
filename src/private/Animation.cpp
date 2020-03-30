
#include <iostream>
#include "../public/Animation.h"
using namespace std;
using namespace sf;

Animation::Animation()
{

}


void Animation::setAnimation(char* nTextura, IntRect firstF, IntRect finalF, int incremento, float tiempo)
{
    if(!texture.loadFromFile(nTextura)){
        cout << "ERROR AL CARGAR TEXTURA";
    }
    this->firstF = firstF;
    this->finalF = finalF;
    this->incremento = incremento;
    actualFrame = firstF;
    switchTime = tiempo;
    sprite = Sprite(texture, actualFrame);
    sprite.setOrigin((firstF.width)/2, (firstF.height)/2);
}
/*
void Animation::update(Vector2f movement, float mTime)
{
    float delta = clock.getElapsedTime().asSeconds();
    if(delta >= switchTime) {
        clock.restart();
        if(actualFrame.left == finalF.left){
            actualFrame.left = firstF.left;
        } else {
            actualFrame.left += incremento;
        }

        sprite.setTextureRect(actualFrame);
    }
    sprite.move(movement* mTime);
}*/

void Animation::update()
{
//    std::cout << "DISPARO" << std::endl;
    float delta = clock.getElapsedTime().asSeconds();
    if(delta >= switchTime) {
        clock.restart();
        if(actualFrame.left == finalF.left){
            actualFrame.left = firstF.left;
        } else {
            actualFrame.left += incremento;
        }

        sprite.setTextureRect(actualFrame);
    }
}


Animation::~Animation() // Destructor
{
    
}


