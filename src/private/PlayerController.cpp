#include "../public/PlayerController.h"

#include <iostream>
#include <list>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <algorithm>

PlayerController::PlayerController(){
    stop = sf::Vector2f(0.0,0.0);
}

void PlayerController::Update(bool pulsada, Player* jugador, sf::Keyboard::Key tecla){
    if(tecla==sf::Keyboard::Up || tecla==sf::Keyboard::W){
        pos1 = sf::Vector2f(jugador->direction.x,jugador->direction.y-0.3);
        jugador->direction = pos1;
        if (pulsada==false){
            directionAux = jugador->direction;
            jugador->direction = directionAux;
        }
    }
    if(tecla==sf::Keyboard::Down || tecla==sf::Keyboard::S){
        pos2 = sf::Vector2f(jugador->direction.x,jugador->direction.y+0.3);
        jugador->direction = pos2;
        if (pulsada==false){
            directionAux = jugador->direction;
            jugador->direction = directionAux;
        }
    }
    if(tecla==sf::Keyboard::Left || tecla==sf::Keyboard::A){
        pos3 = sf::Vector2f(jugador->direction.x-0.3, jugador->direction.y);
        jugador->direction = pos3;
        if (pulsada==false){
            directionAux = jugador->direction;
            jugador->direction = directionAux;
        }
    }
    if(tecla==sf::Keyboard::Right || tecla==sf::Keyboard::D){
        pos4 = sf::Vector2f(jugador->direction.x+0.3, jugador->direction.y);
        jugador->direction = pos4;
        if (pulsada==false){
            directionAux = jugador->direction;
            jugador->direction = directionAux;
        }
    }
}

PlayerController::~PlayerController() // Destructor
{
 
}