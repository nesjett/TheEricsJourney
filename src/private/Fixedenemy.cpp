#include "../public/Fixedenemy.h"

Fixedenemy::Fixedenemy(){ // Use this to call to parent's contructor first
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

bool Fixedenemy::Attack(){

    return true;
}

void Fixedenemy::Shot(Projectile* proj,Player* player){
   Vector2f pos = getActorLocation();
   Vector2f pos_player = player->getActorLocation();
   Vector2f dir = pos_player-pos;
   float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
   Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);
   
   while(relojMark.getElapsedTime().asSeconds()>2){
       
        proj->direction=Vector2f(dir_unit);
        proj->setActorLocation(pos);
        relojMark.restart();
   }
  
}
