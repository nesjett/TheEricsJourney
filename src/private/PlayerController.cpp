#include "../public/PlayerController.h"
#include "../public/game.h"


PlayerController::PlayerController(Player* jugador){
    miJugador = jugador;
}

void PlayerController::Update(sf::Event event){
    if (event.key.code == sf::Keyboard::N){
        MejorarCadencia(0.9);
    }
    if(event.key.code == sf::Keyboard::V){
        MejorarMovimiento(1.1);
    }
    if(event.key.code == sf::Keyboard::P){
        IncreaseHealth();
        std::cout<<"Vida total: "<<getMaxHealth()<<std::endl;
    }
    if(event.key.code == sf::Keyboard::O){
        ImprovesAttack();
    }
    if(event.key.code == sf::Keyboard::G){
        if(Godclock->getElapsedTime().asSeconds()>1.5){
            if(GodMode==true){
                setGodMode(false);
                Godclock->restart();
                std::cout<<"Modo Dios desactivado"<<std::endl;
            }
            else{
                setGodMode(true);
                Godclock->restart();
                std::cout<<"Modo Dios activado"<<std::endl;
            }
        }
    }
    /**
     * MOUSE IMPLEMENTATION
     **/
    if(event.type == sf::Event::MouseButtonPressed){
        if(event.mouseButton.button == sf::Mouse::Left){
            stop=false;
        }
    }

    this->Mover(event);

    if (event.type == sf::Event::MouseButtonReleased){
        this->Frenar();
    }

}
void PlayerController::setGodMode(bool god){
    miJugador->setGodMode(god);
    GodMode=god;
}
void PlayerController::Mover(sf::Event event){
    /*
    Vector2f dir = pos_player-pos;
   float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
   Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);
   */
    /*if(event==sf::Keyboard::Up || event==sf::Keyboard::W){
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
    }*/
    if(stop==false){
        //std::cout << "the left button was pressed" << std::endl;
        //std::cout << "mouse x: " << event.mouseButton.x << std::endl;
        //std::cout << "mouse y: " << event.mouseButton.y << std::endl;

        Engine *eng = Engine::Instance();
        Vector2i pos = sf::Mouse::getPosition(eng->getApp()); // mouse position in window coords
        Vector2f pos2 = eng->getApp().mapPixelToCoords(pos, eng->getApp().getView()); // convert window coords to world coords

        Vector2f PlayerLoc = miJugador->getActorLocation();

        /*if( (PlayerLoc.x >= pos2.x + 0.1 || PlayerLoc.x <= pos2.x -0.1) && (PlayerLoc.y >= pos2.y + 0.1 || PlayerLoc.y <= pos2.y -0.1)) { // Check if player reached mouse location, so we stop movement
            this->Frenar();
            return;
        }*/

        Vector2f newDir = Vector2f(pos2.x, pos2.y) - PlayerLoc; // Determine direction
        float aux=sqrt(pow(newDir.x, 2)+pow(newDir.y, 2));
        Vector2f dir_unit=Vector2f(newDir.x/aux,newDir.y/aux); // convert to unit vector
        miJugador->setDirection(dir_unit.x, dir_unit.y); // apply direction
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
    stop=true;
    miJugador->setDirection(0.f, 0.f);
}

void PlayerController::setPlayer(Player* jugador){
    miJugador = jugador;
}
void PlayerController::MejorarCadencia(float mej){
    mejora*=mej;
    miJugador->cadenciaMultiplier = mejora;
}
void PlayerController::MejorarMovimiento(float mejMov){
    miJugador->movementSpeed*=mejMov;
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