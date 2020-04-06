#include "../public/PlayerController.h"
#include "../public/game.h"


PlayerController::PlayerController(Player* jugador, list<Enemy*> listaEnemigos){
    miJugador = jugador;
    enemyList = listaEnemigos;
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

void PlayerController::setPlayer(Player* jugador){
    miJugador = jugador;
}
void PlayerController::setLista(list<Enemy*> listaEnemigos){
    enemyList = listaEnemigos;
}

void PlayerController::Attacks(){
    //Primero -> Calcular la distancia mas corta de entre todos los enemigos.
    
    if(relojAtaque.getElapsedTime().asSeconds()>2.f){
        sf::Vector2f posPlayer = miJugador->getActorLocation();
        float minDist = 0.f;
        sf::Vector2f dirToEnemy_tmp = sf::Vector2f(0.f, 0.f);
        sf::Vector2f dirToEnemy = sf::Vector2f(0.f, 0.f);
        sf::Vector2f posEnemy = sf::Vector2f(0.f, 0.f);
        
        for (Enemy *enemigo : enemyList){
            posEnemy = enemigo->getActorLocation();
            dirToEnemy_tmp = posEnemy-posPlayer;
            float aux=sqrt(pow(dirToEnemy_tmp.x, 2)+pow(dirToEnemy_tmp.y, 2)); //Esto es la longitud del vector
            if(minDist == 0.f){
                minDist = aux;
                dirToEnemy = dirToEnemy_tmp;
            } else if(aux < minDist){
                minDist = aux;
                dirToEnemy = dirToEnemy_tmp;
            }
        }
        sf::Vector2f dir_unit=Vector2f(dirToEnemy.x/minDist,dirToEnemy.y/minDist);

        game *eng = game::Instance();
        Projectile *projTest = new Projectile(dir_unit, posPlayer);
        eng->Almacenaenemy(projTest);
        relojAtaque.restart();
    }
}

PlayerController::~PlayerController() // Destructor
{
 
}