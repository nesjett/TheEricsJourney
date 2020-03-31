#include "../public/PlayerController.h"

#include <iostream>
#include <list>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <algorithm>

PlayerController::PlayerController(Player* jugador){
    stop = sf::Vector2f(0.0,0.0);
    miJugador = jugador;

}

void PlayerController::Update(bool pulsada, sf::Keyboard::Key tecla){
    if(tecla==sf::Keyboard::Up || tecla==sf::Keyboard::W){
        /*pos1 = sf::Vector2f(miJugador->direction.x,miJugador->direction.y-0.3);
        miJugador->direction = pos1;
        if (pulsada==false){
            directionAux = miJugador->direction;
            miJugador->direction = directionAux;
        }*/
        pos1 = sf::Vector2f(0.0, -0.3);
        miJugador->Movimiento(pos1);
    }
    if(tecla==sf::Keyboard::Down || tecla==sf::Keyboard::S){
        /*pos2 = sf::Vector2f(miJugador->direction.x,miJugador->direction.y+0.3);
        miJugador->direction = pos2;
        if (pulsada==false){
            directionAux = miJugador->direction;
            miJugador->direction = directionAux;
        }*/
        pos2 = sf::Vector2f(0.0, +0.3);
        miJugador->Movimiento(pos2);
    }
    if(tecla==sf::Keyboard::Left || tecla==sf::Keyboard::A){
        /*pos3 = sf::Vector2f(miJugador->direction.x-0.3, miJugador->direction.y);
        miJugador->direction = pos3;
        if (pulsada==false){
            directionAux = miJugador->direction;
            miJugador->direction = directionAux;
        }*/
        pos3 = sf::Vector2f(-0.3, 0.0);
        miJugador->Movimiento(pos3);
    }
    if(tecla==sf::Keyboard::Right || tecla==sf::Keyboard::D){
        /*pos4 = sf::Vector2f(miJugador->direction.x+0.3, miJugador->direction.y);
        miJugador->direction = pos4;
        if (pulsada==false){
            directionAux = miJugador->direction;
            miJugador->direction = directionAux;
        }*/
        pos4 = sf::Vector2f(+0.3, 0.0);
        miJugador->Movimiento(pos4);
    }
    else{
        miJugador->Movimiento(stop);
    }
}

PlayerController::~PlayerController() // Destructor
{
 
}