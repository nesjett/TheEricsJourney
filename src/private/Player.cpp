#include "../public/Player.h"
#include "../public/game.h"
#include "Arrow.h"

Player::Player(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    //texture_file = "./resources/Player.png";
    texture_file = "./resources/Zombies.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(0.f, 0.f);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 5.0f;
    faction = allie;
    AttackImprovement = 0;
    Init();
    PrepareSprite();

}

void Player::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect( 0, 0 ,75,75 );
    

    std::cout << "Terminamos INIT()" << std::endl;
}
void Player::Draw(double percent, double delta ){
    Pawn::SetAnimation();
   Pawn::Draw(percent, delta); 
   

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

void Player::PrepareSprite(){
    //float sizeX = 621.0, sizeY = 569.0;
    float sizeX = 32.0, sizeY = 64.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    //sprite->setScale( 0.1,0.1 );
    double playrate = 1000.0;
    Animation *tmpA;

        //DOWN
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"up", tmpA});
    tmpA->addFrame({sf::IntRect(0,192, sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,192,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,192,sizeX,sizeY), playrate});

    //LEFT
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"right", tmpA});
    tmpA->addFrame({sf::IntRect(0,128,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,128,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,128,sizeX,sizeY), playrate});


    //RIGHT
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"left", tmpA});
    tmpA->addFrame({sf::IntRect(0,64,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,64,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,64,sizeX,sizeY), playrate});


    //UP
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"down", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(64,0,sizeX,sizeY), playrate});
/*    
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"up", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,569,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,569,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,569,sizeX,sizeY), playrate});
   tmpA->addFrame({sf::IntRect(0,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,1707,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,1707,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,1707,sizeX,sizeY), playrate});
    
 
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"right", tmpA});
    
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,569,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,569,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,569,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,1707,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,1707,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,1707,sizeX,sizeY), playrate});
    

    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"left", tmpA});
    
    tmpA->addFrame({sf::IntRect(0,2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,569+2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,569+2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,569+2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,1138+2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,1138+2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,1138+2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,1707+2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,1707+2276,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,1707+2276,sizeX,sizeY), playrate});
    

    
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"down", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,569,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,569,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,569,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,1138,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(0,1707,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(621,1707,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(1242,1707,sizeX,sizeY), playrate});
*/    
}

void Player::TakeDamage(float damage, Actor* dmgCauser, string damage_type){
    std::cout << "Player toke damage!" << std::endl; 
    if(health_Current > 0){ // Only apply damage if the enemy is alive.
        health_Current-=damage;
        if(IsAlive() == false){
            Die();
        } else {
            ApplyHitEffects(damage_type); // Apply hit effects
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


void Player::UpdateMovement(){

}

void Player::ActorOverlap(Actor otherActor){

}


// Base to implement attacks. This should be on the base class and be overriden by the different enemies
void Player::Attack(list<Enemy*> enemyList){
    
    float minDist = 0.f;
    sf::Vector2f posPlayer = getActorLocation();
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
    Arrow *projTest = new Arrow(dir_unit, posPlayer);
    eng->Almacenaenemy(projTest);
    AudioManager* am = AudioManager::getInstance();
    am->play_player_shot();
    if(AttackImprovement >= 1){
        Arrow *projTest1 = new Arrow(-dir_unit, posPlayer);
        eng->Almacenaenemy(projTest1);
        if(AttackImprovement >= 2/* && relojMejora.getElapsedTime().asSeconds()>2*/){
            sf::Vector2f dobleFlecha = sf::Vector2f(getActorLocation().x, (getActorLocation().y-30));
            Arrow *projTest2 = new Arrow(dir_unit, dobleFlecha);
            eng->Almacenaenemy(projTest2);
            //relojMejora.restart();
            if(AttackImprovement >= 3){
                Arrow *projTest3 = new Arrow(-dir_unit, dobleFlecha);
                eng->Almacenaenemy(projTest3);
            }
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