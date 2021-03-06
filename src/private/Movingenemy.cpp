#include "../public/Movingenemy.h"
#include "../public/AudioManager.h"

Movingenemy::Movingenemy(): Enemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/Calavera2.png";


    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.1f;

    setActorLocation(x);


    //Init();
    PrepareSprite();
}

void Movingenemy::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(75/2, 75/2);
    sprite->setTextureRect(75,75,75,75 );
    std::cout << "Terminamos INIT()" << std::endl;
}

void Movingenemy::PrepareSprite(){
    float sizeX = 828.0, sizeY = 896.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale( 0.07,0.07 );
    
    Animation *tmpA;

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"up", tmpA});
    tmpA->addFrame({sf::IntRect(0,1016,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,1912,sizeX,sizeY)});
     
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"right", tmpA});
    tmpA->addFrame({sf::IntRect(828,1016,-sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(828,1912,-sizeX,sizeY)});
    
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"left", tmpA});
    tmpA->addFrame({sf::IntRect(0,1016,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,1912,sizeX,sizeY)});
    
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"down", tmpA});
    tmpA->addFrame({sf::IntRect(0,1016,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,1912,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"stop", tmpA});
    tmpA->addFrame({sf::IntRect(0,1016,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,1912,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"dead", tmpA});
    tmpA->addFrame({sf::IntRect(0,3824,sizeX,sizeY)});
    
}
/*
void Movingenemy::Update(float delta){
    Enemy::Update(delta);

    Linealmove(x,y);
    
    Attack();
}
*/
void Movingenemy::Update(float delta){
    
    
    Enemy::Update(delta);
    if(relojPausa.getElapsedTime().asSeconds()>3.0){//pause to attack
        direction=Vector2f(0.f,0.f);
        if(IsAlive()==true){// while alive he keeps attacking
            Attack();
        }
        
        
        if(relojPausa.getElapsedTime().asSeconds()>5.0){// continue the movement

            relojPausa.restart();
            relojMark.restart();
        }
    }
    else{
        
        direction=ultimadir;
        Linealmove(x,y);
    }
    
    
}

void Movingenemy::Draw(double percent, double delta ){
    this->SetAnimation();
    Enemy::Draw(percent, delta); // Use this to debug draw bounding box
}

void Movingenemy::Prepara(Vector2f inicio, Vector2f final){// set the points between which the enemy moves
    setActorLocation(inicio);
    x=inicio;
    y=final;
}

void Movingenemy::Linealmove(Vector2f pos1, Vector2f pos2){

    Vector2f actor=getActorLocation();
    
    Vector2f dir = pos2-pos1;
    float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));
    Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux); // obtain the direction in which the actor moves

    Vector2f dir2 = pos2-actor;
    float aux2=sqrt(pow(dir2.x, 2)+pow(dir2.y, 2));// and the distance it is from each point
    
    Vector2f dir3 = pos1-actor;
    float aux3=sqrt(pow(dir3.x, 2)+pow(dir3.y, 2));// and the distance it is from each point

    if(pos1.x==actor.x && pos1.y==actor.y){// check to start the movement
        direction = dir_unit;
        
    }
    else{ // if the distance between the player and the point is less than 10 changes direction
        if(aux2<10){
        direction = -dir_unit;
        }
        if(aux3<10){
        direction = dir_unit;
        }
    }
    
    ultimadir=direction;
}


bool Movingenemy::Attack(){
    //Projectile *projTest = new Projectile();
 
    Vector2f pos = getActorLocation();
    game *eng = game::Instance();
    Player* miJugador = eng->getPlayerCharacter();
    //eng->Almacenaenemy(projTest);

   Vector2f pos_player = miJugador->getActorLocation();
   Vector2f dir = pos_player-pos;
   float aux=sqrt(pow(dir.x, 2)+pow(dir.y, 2));//distance between enemy and player
   Vector2f dir_unit=Vector2f(dir.x/aux,dir.y/aux);//get unit direction
   
   if(relojMark.getElapsedTime().asSeconds()>4.0){
       
        //projTest->direction=Vector2f(dir_unit);
        //projTest->setActorLocation(pos);
        Projectile *proj = new Rock(dir_unit, pos); //pass the direction of the player to the projectile
        eng->Almacenaenemy(proj);
        AudioManager::getInstance()->PlaySound2D("./resources/audio/throw.ogg");
        relojMark.restart();
   }
    return true;
}

void Movingenemy::SetAnimation(){// while still alive set the corresponding animation
    
    if(IsAlive()==true){
        Pawn::SetAnimation();
    }
}

void Movingenemy::Die(){// if he dies activates the dead animation
    
    activeAnim=Animations.find("dead")->second;

    setLifespan(1.5);
}