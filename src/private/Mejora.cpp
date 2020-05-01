#include "../public/Mejora.h"
#include "../public/Pawn.h"
#include "../public/game.h"



Mejora::Mejora(PowerUpType tipo) : Actor(){ // Use this to call to parent's contructor first

    texture_file = "./resources/powerups/"+to_string(tipo)+".png";
    oType = powerup;
    tipoMejora = tipo;
    activada = false; //CAMBIAR DESPUES
    PrepareSprite();
}

void Mejora::PrepareSprite(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(sprite->getSprite().getGlobalBounds().width/2, sprite->getSprite().getGlobalBounds().height/2); 
}

void Mejora::Update(float delta){
    if(activada)
        Actor::Update(delta);
}
void Mejora::Draw(double percent, double delta)
{
    if(activada)
        Actor::Draw(percent,delta);
}
void Mejora::OnActorOverlap(Actor *otherActor){
    if (activada == true && dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == allie ) {
        list<Mejora*> listaMejoras = game::Instance()->getMejoras();
        PlayerController* playercontroller = game::Instance()->getPlayerController();
        switch(tipoMejora)
        {
            case health:
                playercontroller->IncreaseHealth();
                break;
            case movementspeed:
                playercontroller->MejorarMovimiento(1.08); //Valores copiados del player controller
                break;
            case attackspeed:
                playercontroller->MejorarCadencia(0.9);
                break;
            case attackmore:
                playercontroller->ImprovesAttack();
                break;   
        }
        //Incluimos mejoras en la hud, guardandola ahi directamente o mediante el player
        
        //Desactivamos todas las mejoras de game porque ya se ha aplicado una
        for(Mejora* mejora : listaMejoras)
        {
            mejora->activada = false;
            mejora->setLifespan(0.f);
        }
    }
}
Mejora::~Mejora() // Destructor
{
 
}