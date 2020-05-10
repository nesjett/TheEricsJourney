#include "../public/Player.h"
#include "../public/game.h"
#include "Arrow.h"
#include "BouncingArrow.h"
#include "../public/AudioManager.h"
#include <list>

Player::Player(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/player.png";


    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(0.f, 0.f);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.2f;
    faction = allie;
    AttackImprovement = 0;
    IncreaseDamage = 0;

    LastAttack = 0;

    Target = nullptr;

    //Init();
    PrepareSprite();
    PrepareMovementIndicator();
}

void Player::Init(){
    float sizeX = 621.0, sizeY = 569.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale( 0.05,0.05 );
}

void Player::PrepareSprite(){
    float sizeX = 550.0, sizeY = 550.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale( 0.14,0.14 );

    sprite->setBounds(0.80);
    
    
    Animation *tmpA;

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"up", tmpA});
    tmpA->addFrame({sf::IntRect(1650,2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1650,550+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,550+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,550+2750,sizeX,sizeY)});
   tmpA->addFrame({sf::IntRect(1650,1100+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,1100+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,1100+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1650,1650+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,1650+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,1650+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1650,2200+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,2200+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,2200+2750,sizeX,sizeY)});
    

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"right", tmpA});
    tmpA->addFrame({sf::IntRect(0,2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,550+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,550+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,550+2750,sizeX,sizeY)});
   tmpA->addFrame({sf::IntRect(0,1100+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,1100+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,1100+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,1650+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,1650+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,1650+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,2200+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,2200+2750,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,2200+2750,sizeX,sizeY)});
    

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"left", tmpA});   
    tmpA->addFrame({sf::IntRect(1650,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1650,550,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,550,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,550,sizeX,sizeY)});
   tmpA->addFrame({sf::IntRect(1650,1100,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,1100,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,1100,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1650,1650,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,1650,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,1650,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1650,2200,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550+1650,2200,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100+1650,2200,sizeX,sizeY)});
    

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"down", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,550,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,550,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,550,sizeX,sizeY)});
   tmpA->addFrame({sf::IntRect(0,1100,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,1100,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,1100,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,1650,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,1650,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,1650,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,2200,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(550,2200,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(1100,2200,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(),500, true);
    Animations.insert({"stopright", tmpA});
    tmpA->addFrame({sf::IntRect(0,2750,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(),500, true);
    Animations.insert({"stopup", tmpA});
    tmpA->addFrame({sf::IntRect(1650,2750,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(),500, true);
    Animations.insert({"stopleft", tmpA});
    tmpA->addFrame({sf::IntRect(1650,0,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(),500, true);
    Animations.insert({"stopdown", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
  
}

int Player::DireccionPausa(){
    Vector2f pos = Target->getActorLocation();
    Vector2f pos_player =getActorLocation();
    Vector2f dir = pos-pos_player;
    float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
    Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);

    auto angleRads = std::atan2(-dir_unit.y, dir_unit.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    if(angleDegs<0){
      angleDegs=angleDegs+360; //los grados van de 0 a 180 y de 0 a -180, sumamos 360 para establecer cuadrantes segun los angulos
    }

    if((angleDegs<22.5 && angleDegs>=0) || (angleDegs>=337.5 && angleDegs<=0)){
        return 1;//right
    }
    if(angleDegs<67.5 && angleDegs>=22.5){
        return 1;//right
    }
    if(angleDegs<112.5 && angleDegs>=67.5){
        return 2;//up
    }
    if(angleDegs<157.5 && angleDegs>=112.5){
        return 3;//left
    }
    if(angleDegs<202.5 && angleDegs>=157.5){
        return 3;//left
    }
    if(angleDegs<247.5 && angleDegs>=202.5){
        return 3;//left
    }
    if(angleDegs<292.5 && angleDegs>=247.5){
        return 4;//down
    }
    if(angleDegs<337.5 && angleDegs>=292.5){
        return 1;//right
    }
}

void Player::SetAnimation(){ //selecciona la animacion del mapa de animaciones dependiendo de la direccion del actor

    auto angleRads = std::atan2(-direction.y, direction.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    if(angleDegs<0){
      angleDegs=angleDegs+360; //los grados van de 0 a 180 y de 0 a -180, sumamos 360 para establecer cuadrantes segun los angulos
    }

    if((angleDegs<22.5 && angleDegs>0) || (angleDegs>=337.5 && angleDegs<360)){
        activeAnim=Animations.find("right")->second;
    }
    if(angleDegs<67.5 && angleDegs>=22.5){
        activeAnim=Animations.find("right")->second;
    }
    if(angleDegs<112.5 && angleDegs>=67.5){
        activeAnim=Animations.find("up")->second;
    }
    if(angleDegs<157.5 && angleDegs>=112.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<202.5 && angleDegs>=157.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<247.5 && angleDegs>=202.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<292.5 && angleDegs>=247.5){
        activeAnim=Animations.find("down")->second;
    }
    if(angleDegs<337.5 && angleDegs>=292.5){
        activeAnim=Animations.find("right")->second;
    }
    if(angleDegs==0){
        if(Target!=nullptr){
            if(DireccionPausa()==1){
                activeAnim=Animations.find("stopright")->second;
            }
            if(DireccionPausa()==2){
                activeAnim=Animations.find("stopup")->second;
            }
            if(DireccionPausa()==3){
                activeAnim=Animations.find("stopleft")->second;
            }
            if(DireccionPausa()==4){
                activeAnim=Animations.find("stopdown")->second;
            }
        }
        else{
            activeAnim=Animations.find("stopup")->second;
        }

        
    }

}

void Player::PrepareMovementIndicator() {
    float sizeX = 508.0, sizeY = 508.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    MovementIndicator = new SSprite("./resources/movement_arrow.png");
    MovementIndicator->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    MovementIndicator->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    MovementIndicator->setScale( 0.07,0.07 );
}

void Player::Draw(double percent, double delta ){
    SetAnimation();
    if(activeAnim) {
        activeAnim->update(delta);
    }
    Pawn::Draw(percent, delta);


    //Movemos la camara 
    Engine* eng = Engine::Instance();
    eng->setView(currentLoc.y, -189.f);


    // Draw movement arrow
    if(MovementIndicator) {
        MovementIndicator->Draw();
        
   
        if(getDirection().x != 0.f || getDirection().y != 0.f) {
            MovementIndicator->getSpriteR().setColor(sf::Color(255,255,255,195)); // Show arrow

            Vector2f newLoc = Vector2f(getDirection().x*45+getInterpolatedPos().x, getDirection().y*45+getInterpolatedPos().y);
            MovementIndicator->setPosition(newLoc.x, newLoc.y);

            // std::atan2 uses y, x signs' for quadrant signification, unlike std::atan
            // SFML's y-axis is flipped: flip our y-component
            auto angleRads = std::atan2(getDirection().y, getDirection().x);
            auto angleDegs = angleRads * 180.0 / M_PI;
            MovementIndicator->setRotation(angleDegs);
        } else {
            MovementIndicator->getSpriteR().setColor(sf::Color(255,255,255,0)); // HIde arrow
        }
    }
 
}

void Player::Update(float delta){
    Pawn::Update(delta);
    SetTarget(this->FindClosestEnemy());
    if(relojAtaque.getElapsedTime().asSeconds()>=0.86f){
        if(relojAtaque.getElapsedTime().asSeconds()>(1.8f*cadenciaMultiplier) && (getDirection().x == 0.f && getDirection().y == 0.f)){
            
            Attack();
            relojAtaque.restart();
        }
    }
}

void Player::TakeDamage(float damage, Actor* dmgCauser, string damage_type){
    //std::cout << "Player toke damage!" << std::endl; 
    if(health_Current > 0&&GodMode==false){ // Only apply damage if the enemy is alive.
        health_Current-=damage;
        if(IsAlive() == false){
            Die();
        } else {
            ApplyHitEffects(damage_type); // Apply hit effects
            game *gi = game::Instance();
            gi->SpawnEmitterAtLocation(0, getActorLocation(), Vector2f(0.f,0.f));
            AudioManager::getInstance()->PlaySound2D("./resources/audio/hit.ogg");
        }
    }
}

void Player::setGodMode(bool god){
    GodMode = god;
}

bool Player::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void Player::Movimiento(sf::Vector2f pos){
    direction = pos;
}
void Player::setDirection(float x, float y){
    direction.x = x;
    direction.y = y;
}
sf::Vector2f Player::getDirection(){
    return direction;
}

void Player::ActorOverlap(Actor otherActor){

}

void Player::SetTarget(Enemy *NewTarget) {
    if(Target) { // Hide marker from last enemy target
        Target->ToggleTarget(false);
    }
    Target = NewTarget; // Set new target (may be null)
    if(Target){ // set new target marker visible
        Target->ToggleTarget(true);
    }
}

Enemy* Player::FindClosestEnemy(){
    float minDist = 0.f;
    sf::Vector2f posPlayer = getActorLocation();
    sf::Vector2f dirToEnemy_tmp = sf::Vector2f(0.f, 0.f);
    sf::Vector2f dirToEnemy = sf::Vector2f(0.f, 0.f);
    sf::Vector2f posEnemy = sf::Vector2f(0.f, 0.f);

    Enemy *enemy = nullptr;

    for (Enemy *enemigo : game::Instance()->getAllEnemies()){
        if(enemigo->IsAlive() == false) {
            continue;
        }
        posEnemy = enemigo->getActorLocation();
        dirToEnemy_tmp = (posEnemy-posPlayer);
        float aux=sqrt(pow(dirToEnemy_tmp.x, 2)+pow(dirToEnemy_tmp.y, 2)); //Esto es la longitud del vector
        if(minDist == 0.f){
            minDist = aux;
            dirToEnemy = dirToEnemy_tmp;
            enemy = enemigo;
        } else if(aux < minDist){
            minDist = aux;
            dirToEnemy = dirToEnemy_tmp;
            enemy = enemigo;
        }
    }
    dir_unit=Vector2f(dirToEnemy.x/minDist,dirToEnemy.y/minDist); // This should not be here

    return enemy;
}

// Base to implement attacks. This should be on the base class and be overriden by the different enemies
void Player::Attack(){
    
    if(!Target){
        return;
    }

    sf::Vector2f posPlayer = getActorLocation();
    sf::Vector2f dobleFlecha = sf::Vector2f(getActorLocation().x-30, (getActorLocation().y)-30);
    //que empiece aqui
    game *eng = game::Instance();
    Arrow *projTest = new Arrow(dir_unit, posPlayer); 
    eng->Almacenaenemy(projTest);

    if(LastAttack == 0) {
        AudioManager::getInstance()->PlaySound2D("./resources/audio/player_shoot.ogg");
    } else {
        AudioManager::getInstance()->PlaySound2D("./resources/audio/player_shoot2.ogg");
    }
    LastAttack++;


    if(AttackImprovement >= 1 && AttackImprovement<4){
        Arrow *flechaTrasera1 = new Arrow(-dir_unit, posPlayer);
        eng->Almacenaenemy(flechaTrasera1);
        if(AttackImprovement >= 2){
            Arrow *flecha2 = new Arrow(dir_unit, dobleFlecha);
            eng->Almacenaenemy(flecha2);
            if(AttackImprovement >= 3){ 
                Arrow *projTest3 = new Arrow(-dir_unit, dobleFlecha);
                eng->Almacenaenemy(projTest3);
            }
        }
    }
    if(AttackImprovement==4){
        BouncingArrow *BA1 = new BouncingArrow(dir_unit, posPlayer); 
        BouncingArrow *BA2 = new BouncingArrow(-dir_unit, posPlayer);
        BouncingArrow *BA3 = new BouncingArrow(dir_unit, dobleFlecha);
        BouncingArrow *BA4 = new BouncingArrow(-dir_unit, dobleFlecha);
        eng->Almacenaenemy(BA1);
        eng->Almacenaenemy(BA2);
        eng->Almacenaenemy(BA3);
        eng->Almacenaenemy(BA4);
    }
    if(IncreaseDamage>0){
        //ModifyDamage();
        for (int i = 0; i < IncreaseDamage; i++){
            ModifyDamage();
        }
    }
}
void Player::improvesAttack(){
    AttackImprovement++;
}
int Player::GetAttackImprove(){
    return AttackImprovement;
}
void Player::IncreaseDamageArrows(){
    IncreaseDamage++;
}
void Player::ModifyDamage(){
    game *eng = game::Instance();
    list<Projectile*> Projectiles = eng->getAllProjectiles();
    for (Projectile* pro : Projectiles){
        if ( dynamic_cast<Arrow*>( pro ) ) {
            dynamic_cast<Arrow*>(pro)->ModifyDamage(1.2f);
        }
    }
    std::cout<<"Daño de flechas aumentado con éxito"<<std::endl;
}
void Player::ModifyCritic(float cri){
    Critic *= cri;
}
float Player::GetCritic(){
    return Critic;
}
void Player::setHealthMax(float increase){
    //In this method, you can set an increase of Player's maximum health
    health_MAX+=increase;
}
void Player::setCurrentH(float increase){
    //In this method, you can set an increse of Player's current health
    //This is made to increase a little bit Player's current health when Player gets a Health Improve.
    health_Current+=increase;
}
float Player::getCurrentHealth(){
    //This method returns the current healt of the player.
    return health_Current;

}
float Player::getMaxHealth(){
    //This method returns the current maximum health of the player. 
    //This is to check if the player has any health improve.
    return health_MAX;

}

void Player::ToggleMovementIndicator() {

}