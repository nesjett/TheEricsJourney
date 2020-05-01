#include "../public/PlayerController.h"
#include "../public/game.h"


PlayerController::PlayerController(Player* jugador, list<Enemy*> listaEnemigos){
    miJugador = jugador;
    enemyList = listaEnemigos;
}

void PlayerController::Update(sf::Event event){
    if (event.key.code == sf::Keyboard::N){
        MejorarCadencia(0.9);
    }
    if(event.key.code == sf::Keyboard::V){
        MejorarMovimiento(1.08);
    }
    if(event.key.code == sf::Keyboard::P){
        IncreaseHealth();
        std::cout<<"Vida total: "<<getMaxHealth()<<std::endl;
    }
    if(event.key.code == sf::Keyboard::O){
        ImprovesAttack();
    }
    //Mover(event.key.code);

    /**
     * MOUSE IMPLEMENTATION
     **/
    if (event.type == sf::Event::MouseButtonPressed)
    {

        if (event.mouseButton.button == sf::Mouse::Left)
        {

            std::cout << "the left button was pressed" << std::endl;
            std::cout << "mouse x: " << event.mouseButton.x << std::endl;
            std::cout << "mouse y: " << event.mouseButton.y << std::endl;

            Engine *eng = Engine::Instance();
            Vector2i pos = sf::Mouse::getPosition(eng->getApp()); // mouse position in window coords
            Vector2f pos2 = eng->getApp().mapPixelToCoords(pos, eng->getApp().getView()); // convert window coords to world coords

            Vector2f newDir = Vector2f(pos2.x, pos2.y) - miJugador->getActorLocation(); // Determine direction
            float aux=sqrt(pow(newDir.x, 2)+pow(newDir.y, 2));
            Vector2f dir_unit=Vector2f(newDir.x/aux,newDir.y/aux); // convert to unit vector
            puntoRaton = pos2;
            miJugador->setDirection(dir_unit.x, dir_unit.y); // apply direction
        }
    }
    std::cout << "Jugador X: " << miJugador->getActorLocation().x << std::endl;
    std::cout << "la horizontal: " << puntoRaton.x << std::endl;
    if(miJugador->getActorLocation().x == puntoRaton.x && miJugador->getActorLocation().y == puntoRaton.y){
        Frenar();
    }
    /*if (sf::Event::MouseButtonReleased){
        if (event.mouseButton.button == sf::Mouse::Left){
            miJugador->setDirection(0.f, 0.f);
            std::cout<<"¿Entras aquí?"<<std::endl;
        }
        
    }*/
    
}
void PlayerController::Mover(sf::Keyboard::Key event){
    /*
    Vector2f dir = pos_player-pos;
   float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
   Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);
   */
    if(event==sf::Keyboard::Up || event==sf::Keyboard::W){
        miJugador->setDirection(0.f, -1);
    }
    if(event==sf::Keyboard::Down || event==sf::Keyboard::S){
        miJugador->setDirection(0.f, 1);
    }
    if(event==sf::Keyboard::Left || event==sf::Keyboard::A){
        miJugador->setDirection(-1.f, 0.f);
    }
    if(event==sf::Keyboard::Right || event==sf::Keyboard::D){
        miJugador->setDirection(1.f, 0.f);
    }

}
void PlayerController::Frenar(/*sf::Keyboard::Key event*/){
    /*if(event==sf::Keyboard::Up || event==sf::Keyboard::W){
        miJugador->setDirection(miJugador->getDirection().x, 0.f);
    }
    if(event==sf::Keyboard::Down || event==sf::Keyboard::S){
        miJugador->setDirection(miJugador->getDirection().x, 0.f);
    }
    if(event==sf::Keyboard::Left || event==sf::Keyboard::A){
        miJugador->setDirection(0.f, miJugador->getDirection().y);
    }
    if(event==sf::Keyboard::Right || event==sf::Keyboard::D){
        miJugador->setDirection(0.f, miJugador->getDirection().y);
    }*/
    miJugador->setDirection(0.f, 0.f);
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
void PlayerController::setAttack(list<Enemy*> listaEnemigos){
    if(miJugador->getDirection().x == 0.f && miJugador->getDirection().y == 0.f && miJugador->IsAlive()==true){
        setLista(listaEnemigos);
        Attacks();
    }
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