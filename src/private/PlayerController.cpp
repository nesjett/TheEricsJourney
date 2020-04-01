#include "../public/PlayerController.h"


PlayerController::PlayerController(Player* jugador){
    stop = sf::Vector2f(0.f,0.f);
    miJugador = jugador;

}

void PlayerController::Update(sf::Keyboard::Key tecla, bool soltada){
    if(tecla==sf::Keyboard::Up || tecla==sf::Keyboard::W){
        if(soltada == true){
            miJugador->setDirection(miJugador->getDirection().x, 0.f);
        }
        else{
            miJugador->setDirection(miJugador->getDirection().x, (-0.05));
        }
    }
    if(tecla==sf::Keyboard::Down || tecla==sf::Keyboard::S){
        if(soltada == true){
            miJugador->setDirection(miJugador->getDirection().x, miJugador->getDirection().y);
        }
        else{
            miJugador->setDirection(miJugador->getDirection().x, 0.05);
        }
    }
    if(tecla==sf::Keyboard::Left || tecla==sf::Keyboard::A){
        if(soltada == true){
            miJugador->setDirection(miJugador->getDirection().x, miJugador->getDirection().y);
        }
        else{
            miJugador->setDirection((-0.05), miJugador->getDirection().y);
        }
    }
    if(tecla==sf::Keyboard::Right || tecla==sf::Keyboard::D){
        if(soltada == true){
            miJugador->setDirection(miJugador->getDirection().x, miJugador->getDirection().y);
        }
        else{
            miJugador->setDirection(0.05, miJugador->getDirection().y);
        }
    }
}

PlayerController::~PlayerController() // Destructor
{
 
}