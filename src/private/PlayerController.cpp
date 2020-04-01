#include "../public/PlayerController.h"


PlayerController::PlayerController(Player* jugador){
    miJugador = jugador;
}

void PlayerController::Update(sf::Keyboard::Key tecla, bool soltada){
    if(soltada == false){

        if(tecla==sf::Keyboard::Up || tecla==sf::Keyboard::W){
            miJugador->setDirection(miJugador->getDirection().x, (-0.05));
            //Move(miJugador->getDirection().x, (-0.05));
        }
        if(tecla==sf::Keyboard::Down || tecla==sf::Keyboard::S){
            miJugador->setDirection(miJugador->getDirection().x, 0.05);
            //Move(miJugador->getDirection().x, 0.05);
        }
        if(tecla==sf::Keyboard::Left || tecla==sf::Keyboard::A){
            miJugador->setDirection((-0.05), miJugador->getDirection().y);
            //Move((-0.05), miJugador->getDirection().y);
        }
        if(tecla==sf::Keyboard::Right || tecla==sf::Keyboard::D){
            miJugador->setDirection(0.05, miJugador->getDirection().y);
            //Move(0.05, miJugador->getDirection().y);
        }
    }
    else{
        miJugador->setDirection(0.f, 0.f);
        //Move(0.f, 0.f);
    }
}

PlayerController::~PlayerController() // Destructor
{
 
}