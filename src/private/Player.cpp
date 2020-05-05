#include "../public/Player.h"
#include "../public/game.h"
#include "Arrow.h"
#include "../public/AudioManager.h"

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
    sprite->setScale( 0.13,0.13 );
    
    
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
    Animations.insert({"stop", tmpA});
    tmpA->addFrame({sf::IntRect(1650,2750,sizeX,sizeY)});
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
    Pawn::SetAnimation();
    Pawn::Draw(percent, delta);


    //Movemos la camara 
    Engine* eng = Engine::Instance();
    eng->setView(currentLoc.y, 0.13f);


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
    /*if(IsAlive()){
        Pawn::Update( delta);
    }*/

    Pawn::Update(delta);
}
void Player::TakeDamage(float damage, Actor* dmgCauser, string damage_type){
    std::cout << "Player toke damage!" << std::endl; 
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

// Base to implement attacks. This should be on the base class and be overriden by the different enemies
void Player::Attack(list<Enemy*> enemyList){
    
    float minDist = 0.f;
    sf::Vector2f posPlayer = getActorLocation();
    sf::Vector2f dirToEnemy_tmp = sf::Vector2f(0.f, 0.f);
    sf::Vector2f dirToEnemy = sf::Vector2f(0.f, 0.f);
    sf::Vector2f posEnemy = sf::Vector2f(0.f, 0.f);

    Enemy *enemy = nullptr;


    for (Enemy *enemigo : enemyList){
        posEnemy = enemigo->getActorLocation();
        dirToEnemy_tmp = posEnemy-posPlayer;
        float aux=sqrt(pow(dirToEnemy_tmp.x, 2)+pow(dirToEnemy_tmp.y, 2)); //Esto es la longitud del vector
        //dirToEnemyParallelAux = sf::Vector2f(posEnemy.x-30, posEnemy.y-30)-getActorLocation();
        //dirToEnemyParallelAux = sf::Vector2f(dirToEnemy_tmp.x*2, dirToEnemy_tmp.y*2);
        //auxParallel = sqrt(pow(dirToEnemyParallel.x, 2)+pow(dirToEnemyParallel.y, 2));
        if(minDist == 0.f){
            minDist = aux;
            dirToEnemy = dirToEnemy_tmp;
            //dirToEnemyParallel = dirToEnemyParallelAux;
            enemy = enemigo;
        } else if(aux < minDist){
            minDist = aux;
            dirToEnemy = dirToEnemy_tmp;
            //dirToEnemyParallel = dirToEnemyParallelAux;
            enemy = enemigo;
        }
    }
    //auxParallel = sqrt(pow(dirToEnemyParallel.x, 2)+pow(dirToEnemyParallel.y, 2));
    sf::Vector2f dir_unit=Vector2f(dirToEnemy.x/minDist,dirToEnemy.y/minDist);
    //dir_unitParallel = Vector2f(dirToEnemyParallel.x/auxParallel, dirToEnemyParallel.y/auxParallel);
    dirToEnemyParallelAux = Vector2f(dir_unit.x*1.5, dir_unit.y*1.5);
    auxParallel = sqrt(pow(dirToEnemyParallelAux.x, 2)+pow(dirToEnemyParallelAux.y, 2));
    dir_unitParallel = Vector2f(dirToEnemyParallelAux.x/auxParallel, dirToEnemyParallelAux.y/auxParallel);

    SetTarget(enemy);

    if(!enemy) { // FInish executing as no eligible enemy found
        return;
    }

    game *eng = game::Instance();
    sf::Vector2f posPlayerAux = sf::Vector2f(getActorLocation().x+30, getActorLocation().y+30);
    Arrow *projTest = new Arrow(dir_unit, posPlayer); //aqui en el segundo parametro antes iba "posPlayer";
    eng->Almacenaenemy(projTest);

    if(LastAttack == 0) {
        AudioManager::getInstance()->PlaySound2D("./resources/audio/player_shoot.ogg");
    } else {
        AudioManager::getInstance()->PlaySound2D("./resources/audio/player_shoot2.ogg");
    }
    LastAttack++;


    if(AttackImprovement >= 1){
        Arrow *flechaTrasera1 = new Arrow(-dir_unit, posPlayer);
        eng->Almacenaenemy(flechaTrasera1);
        if(AttackImprovement >= 2){
            sf::Vector2f dobleFlecha = sf::Vector2f(getActorLocation().x-30, (getActorLocation().y-30));
            Arrow *flecha2 = new Arrow(dir_unitParallel, dobleFlecha);
            eng->Almacenaenemy(flecha2);
            /*if(AttackImprovement >= 3){ //HE COMENTADO ESTO PORQUE ESTOY HACIENDO PRUEBAS
                Arrow *projTest3 = new Arrow(-dir_unit, dobleFlecha);
                eng->Almacenaenemy(projTest3);
            }*/
        }
    }
}
void Player::improvesAttack(){
    AttackImprovement++;
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