#include "../public/PlayerController.h"
#include "../public/game.h"


PlayerController::PlayerController(Player* jugador, list<Enemy*> listaEnemigos){
    miJugador = jugador;
    enemyList = listaEnemigos;
}

void PlayerController::Update(sf::Keyboard::Key tecla, sf::RenderWindow app){
    //game *eng = game::Instance();
    if (tecla == sf::Event::Closed){
        app.close();
    }
    if (tecla == sf::Event::KeyPressed){
        //Escape
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            app.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
            MejorarCadencia(0.9);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
            MejorarMovimiento(1.08);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            IncreaseHealth();
            std::cout<<"Vida total: "<<getMaxHealth()<<std::endl;
        }
        Mover(tecla);
        std::cout << "Tecla pulsada: " << tecla << std::endl;
    }
    if (tecla == sf::Event::KeyReleased){
        Frenar(tecla);
    }
    
}
void PlayerController::Mover(sf::Keyboard::Key tecla){
    if(tecla==sf::Keyboard::Up || tecla==sf::Keyboard::W){
        miJugador->setDirection(miJugador->getDirection().x, (-0.05));
    }
    if(tecla==sf::Keyboard::Down || tecla==sf::Keyboard::S){
        miJugador->setDirection(miJugador->getDirection().x, 0.05);
    }
    if(tecla==sf::Keyboard::Left || tecla==sf::Keyboard::A){
        miJugador->setDirection((-0.05), miJugador->getDirection().y);
    }
    if(tecla==sf::Keyboard::Right || tecla==sf::Keyboard::D){
        miJugador->setDirection(0.05, miJugador->getDirection().y);
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
void PlayerController::MejorarCadencia(float mej){
    mejora*=mej;
}
void PlayerController::MejorarMovimiento(float mejMov){
    miJugador->movementSpeed*=mejMov;
}

void PlayerController::Attacks(){
    
    if(relojAtaque.getElapsedTime().asSeconds()>(2.f*mejora)){
        miJugador->Attack(enemyList);
        relojAtaque.restart();
    }
}
void PlayerController::ImprovesAttack(){
    miJugador->improvesAttack();
}
void PlayerController::IncreaseHealth(){
    //In this method, you can set an increase of 25 HP in Player's health
    miJugador->setHealthMax(25.f);
    miJugador->setCurrentH(25.f);
}
float PlayerController::getCurrentHealth(){
    //This method returns the current health 
    return miJugador->getCurrentHealth();
}
float PlayerController::getMaxHealth(){
    return miJugador->getMaxHealth();
}
PlayerController::~PlayerController() // Destructor
{
 
}