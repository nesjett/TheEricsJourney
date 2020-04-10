#include "../public/PlayerController.h"
#include "../public/game.h"


PlayerController::PlayerController(Player* jugador, list<Enemy*> listaEnemigos){
    miJugador = jugador;
    enemyList = listaEnemigos;
}

void PlayerController::Update(sf::Keyboard::Key tecla){

    if(tecla==sf::Keyboard::Up || tecla==sf::Keyboard::W){
        miJugador->setDirection(miJugador->getDirection().x, (-0.05));
    }
    if(tecla==sf::Keyboard::Down || tecla==sf::Keyboard::S){
        miJugador->setDirection(miJugador->getDirection().x, 0.05);
    }
    if(tecla==sf::Keyboard::Left || tecla==sf::Keyboard::A){
        miJugador->setDirection((-0.05), miJugador->getDirection().y);
        //_izquierda = true;
    }
    if(tecla==sf::Keyboard::Right || tecla==sf::Keyboard::D){
        miJugador->setDirection(0.05, miJugador->getDirection().y);
        //_derecha = true;
    }
}
void PlayerController::Frenar(sf::Keyboard::Key tecla){
    if(tecla==sf::Keyboard::Up || tecla==sf::Keyboard::W){
        miJugador->setDirection(miJugador->getDirection().x, 0.f);
    }
    if(tecla==sf::Keyboard::Down || tecla==sf::Keyboard::S){
        miJugador->setDirection(miJugador->getDirection().x, 0.f);
    }
    if(tecla==sf::Keyboard::Left || tecla==sf::Keyboard::A){
        miJugador->setDirection(0.f, miJugador->getDirection().y);
    }
    if(tecla==sf::Keyboard::Right || tecla==sf::Keyboard::D){
        miJugador->setDirection(0.f, miJugador->getDirection().y);
    }
}

void PlayerController::setPlayer(Player* jugador){
    miJugador = jugador;
}
void PlayerController::setLista(list<Enemy*> listaEnemigos){
    enemyList = listaEnemigos;
}

void PlayerController::Attacks(){
    
    if(relojAtaque.getElapsedTime().asSeconds()>2.f){
        miJugador->Attack(enemyList);
        relojAtaque.restart();
    }
}

PlayerController::~PlayerController() // Destructor
{
 
}