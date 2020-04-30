#include "../public/Fixedenemy.h"

#include <FireBall.h>

Fixedenemy::Fixedenemy(): Enemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(0.f, 0.f);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.1f;

    setActorLocation(Vector2f(340.0, 520.0));

    Init();

}

void Fixedenemy::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect(75,75,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}

void Fixedenemy::Update(float delta){
    Enemy::Update(delta);
    Attack();
}

bool Fixedenemy::Attack(){
    //Projectile *projTest = new Projectile();
 
    Vector2f pos = getActorLocation();
    game *eng = game::Instance();
    Player* miJugador = eng->getPlayerCharacter();
    //eng->Almacenaenemy(projTest);

   Vector2f pos_player = miJugador->getActorLocation();
   Vector2f dir = pos_player-pos;
   float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
   Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);
   
   if(relojMark.getElapsedTime().asSeconds()>3){
       
        //projTest->direction=Vector2f(dir_unit);
        //projTest->setActorLocation(pos);
        FireBall *projTest = new FireBall(dir_unit, pos);
        eng->Almacenaenemy(projTest);
        relojMark.restart();
   }
    return true;
}
