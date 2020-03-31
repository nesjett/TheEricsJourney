#include "../public/PlayerController.h"


PlayerController::PlayerController(Player* jugador){
    stop = sf::Vector2f(0.f,0.f);
    miJugador = jugador;

}

void PlayerController::Update(sf::Keyboard::Key tecla, bool soltada){
    if(tecla==sf::Keyboard::Up || tecla==sf::Keyboard::W){
        /*pos1 = sf::Vector2f(miJugador->direction.x,miJugador->direction.y-0.3);
        miJugador->direction = pos1;
        if (pulsada==false){
            directionAux = miJugador->direction;
            miJugador->direction = directionAux;
        }*/
        //miJugador->Movimiento(sf::Vector2f(0.f, -0.05));
        if(soltada == true){
            miJugador->setDirection(miJugador->getDirection().x, miJugador->getDirection().y);
        }
        else{
            miJugador->setDirection(0.f, (-0.05));
        }
    }
    if(tecla==sf::Keyboard::Down || tecla==sf::Keyboard::S){
        /*pos2 = sf::Vector2f(miJugador->direction.x,miJugador->direction.y+0.3);
        miJugador->direction = pos2;
        if (pulsada==false){
            directionAux = miJugador->direction;
            miJugador->direction = directionAux;
        }*/
        //miJugador->Movimiento(sf::Vector2f(0.f, +0.05));
        if(soltada == true){
            miJugador->setDirection(miJugador->getDirection().x, miJugador->getDirection().y);
        }
        else{
            miJugador->setDirection(0.f, 0.05);
        }
    }
    /*else{
        miJugador->setDirection(0.f, 0.f);
    }*/
    if(tecla==sf::Keyboard::Left || tecla==sf::Keyboard::A){
        /*pos3 = sf::Vector2f(miJugador->direction.x-0.3, miJugador->direction.y);
        miJugador->direction = pos3;
        if (pulsada==false){
            directionAux = miJugador->direction;
            miJugador->direction = directionAux;
        }*/
        //miJugador->Movimiento(sf::Vector2f(-0.05, 0.f));
        if(soltada == true){
            miJugador->setDirection(miJugador->getDirection().x, miJugador->getDirection().y);
        }
        else{
            miJugador->setDirection((-0.05), 0.f);
        }
    }
    if(tecla==sf::Keyboard::Right || tecla==sf::Keyboard::D){
        /*pos4 = sf::Vector2f(miJugador->direction.x+0.3, miJugador->direction.y);
        miJugador->direction = pos4;
        if (pulsada==false){
            directionAux = miJugador->direction;
            miJugador->direction = directionAux;
        }*/
        //miJugador->Movimiento(sf::Vector2f(+0.05, 0.f));
        if(soltada == true){
            miJugador->setDirection(miJugador->getDirection().x, miJugador->getDirection().y);
        }
        else{
            miJugador->setDirection(0.05, 0.f);
        }
    }
    /*else{
        //miJugador->Movimiento(stop);
        miJugador->setDirection(miJugador->getDirection().x, miJugador->getDirection().y);
    }*/
}

PlayerController::~PlayerController() // Destructor
{
 
}