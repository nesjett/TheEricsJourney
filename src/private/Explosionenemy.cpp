#include "../public/Explosionenemy.h"

Explosionenemy::Explosionenemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(0.f, 0.f);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.05f;

    setActorLocation(Vector2f(340.0, 520.0));


    Init();

}

void Explosionenemy::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect(75,75,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}

void Explosionenemy::Update(float delta){
    Pawn::Update(delta);
    Attack();
}

void Explosionenemy::Draw(double percent, double delta ){
    
    Actor::Draw(percent, delta); // Use this to debug draw bounding box
}


void Explosionenemy::Followplayer(){
    Vector2f pos = getActorLocation();
    game *eng = game::Instance();
    Player* miJugador = eng->getPlayerCharacter();
    //eng->Almacenaenemy(projTest);

   Vector2f pos_player = miJugador->getActorLocation();
   Vector2f dir = pos_player-pos;
   float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
   Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);
   direction = dir_unit;
}

bool Explosionenemy::Attack(){
    //Projectile *projTest = new Projectile();
 
    Vector2f pos = getActorLocation();
    game *eng = game::Instance();
    
    Vector2f dir_unit=Vector2f(1.f, 1.f);
    Vector2f dir_unit1=Vector2f(-1.f, -1.f);
    Vector2f dir_unit2=Vector2f(-1.f, 1.f);
    Vector2f dir_unit3=Vector2f(1.f, -1.f);
    
   if(relojMark.getElapsedTime().asSeconds()>6.0){
       
        //projTest->direction=Vector2f(dir_unit);
        //projTest->setActorLocation(pos);
        Projectile *projTest = new Projectile(dir_unit, pos);
        Projectile *projTest1 = new Projectile(dir_unit1, pos);
        Projectile *projTest2 = new Projectile(dir_unit2, pos);
        Projectile *projTest3 = new Projectile(dir_unit3, pos);

        eng->Almacenaenemy(projTest);
        eng->Almacenaenemy(projTest1);
        eng->Almacenaenemy(projTest2);
        eng->Almacenaenemy(projTest3);

        relojMark.restart();
   }
    return true;
}
/*
Vector2f Explosionenemy::Direccionunitaria(Vector2f pos_player,Vector2f pos){
    Vector2f dir = pos_player-pos;
   float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
   Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);
   return dir_unit;
}
*/