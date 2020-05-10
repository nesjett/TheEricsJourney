#include "../public/PlayerController.h"
#include "../public/game.h"


PlayerController::PlayerController(Player* jugador){
    miJugador = jugador; //Linking the PlayerController with a Player
}
void PlayerController::Update(sf::Event event){ /*Key Events are handled in this method.
    First of all, there is the special key section to make easier the videogame correction.*/
    if (event.key.code == sf::Keyboard::Q && event.type == sf::Event::KeyReleased){
        MejorarCadencia(0.9); //Cadence is increased 0.9 times.
    }
    if(event.key.code == sf::Keyboard::W && event.type == sf::Event::KeyReleased){
        MejorarMovimiento(1.1); //Player speed is increased 1.1 times
    }
    if(event.key.code == sf::Keyboard::E && event.type == sf::Event::KeyReleased){
        IncreaseHealth(); //Call to health boost method
        std::cout<<"Vida total: "<<getMaxHealth()<<std::endl; //Print to console Player's Max Health 
    }
    if(event.key.code == sf::Keyboard::R && event.type == sf::Event::KeyReleased){
        ImprovesAttack(); //Attack Increase method call. Player will shoot more arrows.
    }
    if(event.key.code == sf::Keyboard::T && event.type == sf::Event::KeyReleased){
        ModifyDamage(); //With this method the player will do more damage to enemies
    }
    if(event.key.code == sf::Keyboard::Y && event.type == sf::Event::KeyReleased){
        ModifyCritic(0.96); //Possibility of making a critical hit is increased
    }
    if(event.key.code == sf::Keyboard::G && event.type == sf::Event::KeyReleased){
        //God Mode to make the Player invulnerable and make easier the game correction
        if(Godclock->getElapsedTime().asSeconds()>1.5){
            if(GodMode==true){
                setGodMode(false); //Desactivate GodMode
                Godclock->restart(); //Restart the clock
                std::cout<<"Modo Dios desactivado"<<std::endl; //Show it on the console
            }
            else{
                setGodMode(true); //Activate GodMode
                Godclock->restart(); //Restart the clock
                std::cout<<"Modo Dios activado"<<std::endl; //Show it on the console
            }
        }
    }
    /**
     * MOUSE IMPLEMENTATION
     **/
    if(event.type == sf::Event::MouseButtonPressed){
        if(event.mouseButton.button == sf::Mouse::Left){
            stop=false; //Bool in false --> Player doesn't stop and continue moving
        }
    }

    this->Mover(); //Moving method

    if (event.type == sf::Event::MouseButtonReleased){
        this->Frenar(); //Stopping method
    }

}
void PlayerController::setGodMode(bool god){
    //Method to set the GodMode in the Player
    miJugador->setGodMode(god);
    GodMode=god;
}
void PlayerController::Mover(){
    if(stop==false){

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
    miJugador->setDirection(0.f, 0.f); //The Player direction is set to zero so it can't move.
}
void PlayerController::MejorarCadencia(float mej){
    mejora*=mej;
    if(mejora>=0.47f){ //This limits the improve in the HUD.
        Hud::Instance()->addMejora(attackspeed);
    }
    miJugador->cadenciaMultiplier = mejora; //The internal limitation is set in the Player's method.
}
void PlayerController::MejorarMovimiento(float mejMov){
    if(miJugador->movementSpeed<=0.5f){ //This limits the speed improvement both internal and in the HUD
        Hud::Instance()->addMejora(movementspeed);
        miJugador->movementSpeed*=mejMov;
    }
}
void PlayerController::ImprovesAttack(){
    miJugador->improvesAttack(); //Player will shoot more arrows
    if(miJugador->GetAttackImprove()<=4){ //This limits this improvement in the HUD
        Hud::Instance()->addMejora(attackmore);
    }
}
void PlayerController::IncreaseHealth(){
    //In this method, you can set an increase of 25 HP in Player's health
    miJugador->setHealthMax(25.f);
    miJugador->setCurrentH(25.f);
    Hud::Instance()->addMejora(health); //Show on the HUD that Player has health increased.
}
float PlayerController::getCurrentHealth(){
    //This method returns the current health 
    return miJugador->getCurrentHealth();
}
float PlayerController::getMaxHealth(){
    //This method returns the Max health of the Player
    return miJugador->getMaxHealth();
}
void PlayerController::ModifyDamage(){
    //This method increase the damage of Player's arrows
    miJugador->IncreaseDamageArrows();
    Hud::Instance()->addMejora(moredamage); //Show on the HUD that Player has Damage Increased.
}
void PlayerController::ModifyCritic(float cri){
    //This method increases the possibility of making a critical hit
    miJugador->ModifyCritic(cri);
    Hud::Instance()->addMejora(critattack); //Show that in the HUD.
}
PlayerController::~PlayerController() // Destructor
{
 
}