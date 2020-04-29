#include "../public/Explosionenemy.h"

#include <FireBall.h>

Explosionenemy::Explosionenemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(-0.5, -0.5);

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
    Followplayer();
    Attack();
    
}

void Explosionenemy::Draw(double percent, double delta ){
    
    Actor::Draw(percent, delta); // Use this to debug draw bounding box
}


void Explosionenemy::Followplayer(){
    
    if(relojdireccion.getElapsedTime().asSeconds()>4.0){
        direction=RandomNewDir();
        relojdireccion.restart(); 
    }
   
}

Vector2f Explosionenemy::RandomNewDir() {
    std::vector<Vector2f> possibleDir = {Vector2f(0.0, -1.0), Vector2f(0.0, 1.0), Vector2f(-1.0, 0.0), Vector2f(1.0, 0.0), Vector2f(1.0, 1.0), Vector2f(-1.0, 1.0), Vector2f(-1.0, -1.0), Vector2f(1.0, -1.0)};
    std::random_shuffle ( possibleDir.begin(), possibleDir.end() );
    return possibleDir.front();
    //return Vector2f(0.f, 0.f);
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
        FireBall *projTest = new FireBall(dir_unit, pos);
        FireBall *projTest1 = new FireBall(dir_unit1, pos);
        FireBall *projTest2 = new FireBall(dir_unit2, pos);
        FireBall *projTest3 = new FireBall(dir_unit3, pos);

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