#include "../public/Player.h"
#include "../public/game.h"
#include "Arrow.h"
#include "../public/AudioManager.h"

Player::Player(){ // Use this to call to parent's contructor first
    texture_file2 = "./resources/sprites.png";

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

    Init();

}

void Player::Init(){
    sprite = new SSprite(texture_file2);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect( 0, 0 ,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}
void Player::Draw(double percent, double delta ){
   Actor::Draw(percent, delta);

    //Movemos la camara 
    Engine* eng = Engine::Instance();
    eng->setView(currentLoc.y, 0.13f);
 
}

void Player::Update(float delta){
    bool estado=IsAlive();
    if(estado==true){
        Pawn::Update( delta);
    }
    
}
void Player::TakeDamage(float damage, Actor* dmgCauser, string damage_type){
    std::cout << "Player toke damage!" << std::endl; 
    if(health_Current > 0){ // Only apply damage if the enemy is alive.
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
        dirToEnemyParallelAux = sf::Vector2f(posEnemy.x-30, posEnemy.y)-getActorLocation();
        if(minDist == 0.f){
            minDist = aux;
            dirToEnemy = dirToEnemy_tmp;
            dirToEnemyParallel = dirToEnemyParallelAux;
            enemy = enemigo;
        } else if(aux < minDist){
            minDist = aux;
            dirToEnemy = dirToEnemy_tmp;
            dirToEnemyParallel = dirToEnemyParallelAux;
            enemy = enemigo;
        }
    }
    auxParallel = sqrt(pow(dirToEnemyParallel.x, 2)+pow(dirToEnemyParallel.y, 2));
    sf::Vector2f dir_unit=Vector2f(dirToEnemy.x/minDist,dirToEnemy.y/minDist);
    dir_unitParallel = Vector2f(dirToEnemyParallel.x/auxParallel, dirToEnemyParallel.y/auxParallel);

    SetTarget(enemy);

    game *eng = game::Instance();
    Arrow *projTest = new Arrow(dir_unit, posPlayer);
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
            sf::Vector2f dobleFlecha = sf::Vector2f(getActorLocation().x-30, (getActorLocation().y));
            Arrow *flecha2 = new Arrow(dir_unitParallel, dobleFlecha);
            eng->Almacenaenemy(flecha2);
            /*if(AttackImprovement >= 3){
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