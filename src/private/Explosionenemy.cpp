#include "../public/Explosionenemy.h"

#include <FireBall.h>

Explosionenemy::Explosionenemy():Enemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/Naranja.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(-0.5, -0.5);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.05f;

    setActorLocation(Vector2f(340.0, 520.0));


    //Init();
    PrepareSprite();

}

void Explosionenemy::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect(75,75,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}

void Explosionenemy::PrepareSprite(){
    float sizeX = 212.0, sizeY = 235.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale( 0.25,0.25 );
    
    Animation *tmpA;

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"up", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,235,sizeX,sizeY)});

    
 
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"right", tmpA});
    
    tmpA->addFrame({sf::IntRect(212,0,-sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(212,235,-sizeX,sizeY)});
    

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"left", tmpA});
    
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,235,sizeX,sizeY)});
    

    
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"down", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,235,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"dead", tmpA});
    tmpA->addFrame({sf::IntRect(0,470,sizeX,sizeY)});
}

void Explosionenemy::Update(float delta){
    
    
    Enemy::Update(delta);
    if(relojPausa.getElapsedTime().asSeconds()>1.0){//pause to attack
        direction=Vector2f(0.f,0.f);
        if(IsAlive()==true){ // while alive he keeps attacking
            Attack();
        }
        
        if(relojPausa.getElapsedTime().asSeconds()>4.0){ // continue the movement
            relojPausa.restart();
            relojMark.restart();
        }
    }
    else{
        
        Followplayer();
        
    }
    
    
}

void Explosionenemy::Draw(double percent, double delta ){
    this->SetAnimation();
    Enemy::Draw(percent, delta); // Use this to debug draw bounding box
}


void Explosionenemy::Followplayer(){
    
    if(relojdireccion.getElapsedTime().asSeconds()>2.0){ //change of direction every 2 seconds
        direction=RandomNewDir();
        relojdireccion.restart(); 
    }
   
}

Vector2f Explosionenemy::RandomNewDir() { // get random direction
    std::vector<Vector2f> possibleDir = {Vector2f(0.0, -1.0), Vector2f(0.0, 1.0), Vector2f(-1.0, 0.0), Vector2f(1.0, 0.0), Vector2f(1.0, 1.0), Vector2f(-1.0, 1.0), Vector2f(-1.0, -1.0), Vector2f(1.0, -1.0)};
    std::random_shuffle ( possibleDir.begin(), possibleDir.end() );
    return possibleDir.front();
    //return Vector2f(0.f, 0.f);
}

bool Explosionenemy::Attack(){ //generates 4 projectiles in different directions
    //Projectile *projTest = new Projectile();
 
    Vector2f pos = getActorLocation();
    game *eng = game::Instance();
    
    Vector2f dir_unit=Vector2f(1.f, 1.f);
    Vector2f dir_unit1=Vector2f(-1.f, -1.f);
    Vector2f dir_unit2=Vector2f(-1.f, 1.f);
    Vector2f dir_unit3=Vector2f(1.f, -1.f);
    
   if(relojMark.getElapsedTime().asSeconds()>3.0){
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

void Explosionenemy::SetAnimation(){// while still alive set the corresponding animation
    
    if(IsAlive()==true){
        Pawn::SetAnimation();
    }
}

void Explosionenemy::Die(){// if he dies activates the dead animation
    
    activeAnim=Animations.find("dead")->second;

    setLifespan(1.5);
}