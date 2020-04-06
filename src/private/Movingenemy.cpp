#include "../public/Movingenemy.h"

Movingenemy::Movingenemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    
    

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.1f;

    


    Init();

}

void Movingenemy::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect(75,75,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}

void Movingenemy::Update(float delta){
    Pawn::Update(delta);
    Attack();
}

void Movingenemy::Draw(double percent, double delta ){
    Actor::Draw(percent, delta); // Use this to debug draw bounding box
}

void Movingenemy::Linealmove_y(float pos1, float pos2){

    if(pos1!=pos2){
        if(pos1<pos2){
            float aux=pos2;
            pos2=pos1;
            pos1=aux;    
        }

        if(getActorLocation().y>=pos1){
            enemydirection_y=-1.0;
        }
        if(getActorLocation().y<=pos2){
            enemydirection_y=1.0;
        }
    }
    else{
        enemydirection_y=0.0;
    }

    direction = Vector2f(0.0,enemydirection_y);
}

void Movingenemy::Linealmove_x(float pos1, float pos2){

    if(pos1!=pos2){
        if(pos1<pos2){
            float aux=pos2;
            pos2=pos1;
            pos1=aux;    
        }

        if(getActorLocation().x>=pos1){
            enemydirection_x=-1.0;
        }
        if(getActorLocation().x<=pos2){
            enemydirection_x=1.0;
        }
    }
    else{
        enemydirection_x=0.0;
    }

    direction = Vector2f(enemydirection_x,0.0);
}


bool Movingenemy::Attack(){
    //Projectile *projTest = new Projectile();
 
    Vector2f pos = getActorLocation();
    game *eng = game::Instance();
    Player* miJugador = eng->getPlayerCharacter();
    //eng->Almacenaenemy(projTest);

   Vector2f pos_player = miJugador->getActorLocation();
   Vector2f dir = pos_player-pos;
   float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
   Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);
   
   if(relojMark.getElapsedTime().asSeconds()>5.0){
       
        //projTest->direction=Vector2f(dir_unit);
        //projTest->setActorLocation(pos);
        Projectile *projTest = new Projectile(dir_unit, pos);
        eng->Almacenaenemy(projTest);
        relojMark.restart();
   }
    return true;
}