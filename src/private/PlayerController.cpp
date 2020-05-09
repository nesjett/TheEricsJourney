#include "../public/PlayerController.h"
#include "../public/game.h"


PlayerController::PlayerController(Player* jugador){
    miJugador = jugador;
}
void PlayerController::Update(sf::Event event){
    if (event.key.code == sf::Keyboard::Q){
        MejorarCadencia(0.9);
        Hud::Instance()->addMejora(attackspeed);
    }
    if(event.key.code == sf::Keyboard::W){
        MejorarMovimiento(1.1);
        Hud::Instance()->addMejora(movementspeed);
    }
    if(event.key.code == sf::Keyboard::E){
        IncreaseHealth();
        std::cout<<"Vida total: "<<getMaxHealth()<<std::endl;
        Hud::Instance()->addMejora(health);
    }
    if(event.key.code == sf::Keyboard::R){
        ImprovesAttack();
        Hud::Instance()->addMejora(attackmore);
    }
    if(event.key.code == sf::Keyboard::T){
        ModifyDamage();
        Hud::Instance()->addMejora(moredamage);
    }
    if(event.key.code == sf::Keyboard::Y){
        Hud::Instance()->addMejora(critattack);
        ModifyCritic(0.96);
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
    if(stop==false){
        //std::cout << "the left button was pressed" << std::endl;
        //std::cout << "mouse x: " << event.mouseButton.x << std::endl;
        //std::cout << "mouse y: " << event.mouseButton.y << std::endl;

        Engine *eng = Engine::Instance();
        Vector2i pos = sf::Mouse::getPosition(eng->getApp()); // mouse position in window coords
        Vector2f pos2 = eng->getApp().mapPixelToCoords(pos, eng->getApp().getView()); // convert window coords to world coords

        Vector2f PlayerLoc = miJugador->getActorLocation();

        Vector2f newDir = Vector2f(pos2.x, pos2.y) - PlayerLoc; // Determine direction
        float aux=sqrt(pow(newDir.x, 2)+pow(newDir.y, 2));
        Vector2f dir_unit=Vector2f(newDir.x/aux,newDir.y/aux); // convert to unit vector
        miJugador->setDirection(dir_unit.x, dir_unit.y); // apply direction
    }
}
void PlayerController::Frenar(){
    stop=true;
    miJugador->setDirection(0.f, 0.f);
}
void PlayerController::MejorarCadencia(float mej){
    mejora*=mej;
    miJugador->cadenciaMultiplier = mejora;
}
void PlayerController::MejorarMovimiento(float mejMov){
    if(miJugador->movementSpeed<=0.5f){
        miJugador->movementSpeed*=mejMov;
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
void PlayerController::ModifyDamage(){
    miJugador->IncreaseDamageArrows();
}
void PlayerController::ModifyCritic(float cri){
    miJugador->ModifyCritic(cri);
}
PlayerController::~PlayerController() // Destructor
{
 
}