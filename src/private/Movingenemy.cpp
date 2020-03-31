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
    //std::cout << "Iniciamos UPDATE()" << std::endl;
    float x = movementSpeed*direction.x*delta;
    float y = movementSpeed*direction.y*delta;
    x = getActorLocation().x + x;
    y = getActorLocation().y + y;
    if(direction.x != 0.f || direction.y != 0.f) {
        UpdateMovement( Vector2f (x,y) );
    }
}

void Movingenemy::Draw(double percent, double delta ){
    animation->update(delta);
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
