#include "../public/Fixedenemy.h"

#include <FireBall.h>

Fixedenemy::Fixedenemy(): Enemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/Planta.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(0.f, 0.f);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.1f;

    setActorLocation(Vector2f(340.0, 520.0));

    //Init();
    PrepareSprite();
}

void Fixedenemy::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect(75,75,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}

void Fixedenemy::PrepareSprite(){
    float sizeX = 376.0, sizeY = 500.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale( 0.1,0.1 );
    
    Animation *tmpA;

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"up", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,500,sizeX,sizeY)});

    
 
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"right", tmpA});
    tmpA->addFrame({sf::IntRect(376,0,-sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(376,500,-sizeX,sizeY)});
    

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"left", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,500,sizeX,sizeY)});
    

    
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"down", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,500,sizeX,sizeY)});
}

void Fixedenemy::Update(float delta){
    Enemy::Update(delta);
    Attack();
}

void Fixedenemy::Draw(double percent, double delta ){
    Pawn::SetAnimation();
    Enemy::Draw(percent, delta); // Use this to debug draw bounding box
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
   direction=dir_unit;
   if(relojMark.getElapsedTime().asSeconds()>3){
       
        //projTest->direction=Vector2f(dir_unit);
        //projTest->setActorLocation(pos);
        FireBall *projTest = new FireBall(dir_unit, pos);
        eng->Almacenaenemy(projTest);
        relojMark.restart();
   }
    return true;
}
