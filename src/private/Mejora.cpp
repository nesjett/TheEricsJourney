#include "../public/Mejora.h"
#include "../public/Pawn.h"
#include "../public/game.h"
#include "../public/Hud.h"



Mejora::Mejora(PowerUpType tipo) : Actor(){ // Use this to call to parent's contructor first

    texture_file = "./resources/powerups/"+to_string(tipo)+".png";
    tipoMejora = tipo;
    switch(tipoMejora)
    {
        case health:
            nombre = "Vida max aumentada";
            break;
        case movementspeed:
            nombre = "Mayor movimiento";
            break;
        case attackspeed:
            nombre = "Mayor cadencia";
            break;
        case attackmore:
            nombre = "Ataque mejorado";
            break;   
        }
    oType = powerup;
    activada = false;
    utilizada = false;
    PrepareSprite();
}
Sprite Mejora::getSprite()
{
    return sprite->getSprite();
}
void Mejora::PrepareSprite(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(sprite->getSprite().getGlobalBounds().width/2, sprite->getSprite().getGlobalBounds().height/2);
    
    dialog = new SSprite("./resources/powerups/"+to_string(tipoMejora)+"_d.png");
    dialog->setOrigin(dialog->getSprite().getGlobalBounds().width/2, dialog->getSprite().getGlobalBounds().height/2);
    dialog->setScale(0.15,0.15);
}

void Mejora::Update(float delta){
    Actor::Update(delta);
}
void Mejora::Draw(double percent, double delta)
{
    if(activada) {
        Actor::Draw(percent,delta);

        if(dialog) {
            dialog->setPosition(getActorLocation().x, getActorLocation().y-50);
            dialog->Draw();
        }
    }
}
void Mejora::OnActorOverlap(Actor *otherActor){
    if (activada == true && dynamic_cast<Pawn*>(otherActor) && dynamic_cast<Pawn*>(otherActor)->getFaction() == allie ) {
        //list<Mejora*> listaMejoras = game::Instance()->getMejoras();
        PlayerController* playercontroller = game::Instance()->getPlayerController();
        switch(tipoMejora)
        {
            case health:
                playercontroller->IncreaseHealth();
                break;
            case movementspeed:
                playercontroller->MejorarMovimiento(1.1); //Valores copiados del player controller
                break;
            case attackspeed:
                playercontroller->MejorarCadencia(0.9);
                break;
            case attackmore:
                playercontroller->ImprovesAttack();
                break;   
            case moredamage:
                playercontroller->ModifyDamage();
                break;
            case critattack:
                playercontroller->ModifyCritic(0.96);
                break;
        }
        //Incluimos mejoras en la hud, guardandola ahi directamente o mediante el player
        Hud::Instance()->addMejora(tipoMejora);
        //Desactivamos todas las mejoras de game porque ya se ha aplicado una
        for(Mejora* mejora : game::Instance()->getMejoras())
        {
            mejora->utilizada = true;
            mejora->activada = false;
            mejora->setLifespan(0.f);
            //mejora->pendingDelete=true;
        }
        game *gi = game::Instance();
        gi->SpawnEmitterAtLocation(2, getActorLocation(), Vector2f(0.f,0.f));
        AudioManager::getInstance()->PlaySound2D("./resources/audio/health-improve.ogg");
    }
}