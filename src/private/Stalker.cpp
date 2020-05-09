#include "../public/Stalker.h"

Stalker::Stalker(): Enemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/Volador.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(0.f, 0.f);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.05f;

    setActorLocation(Vector2f(340.0, 520.0));


    //Init();
    PrepareSprite();

}

void Stalker::Init(){
    sprite = new SSprite(texture_file);
    sprite->setOrigin(401/2, 249/2);
    sprite->setTextureRect(0,0,401,249 );
    std::cout << "Terminamos INIT()" << std::endl;
    
    sprite->setScale(0.2,0.2);

    Animation *tmpA;

    //IDLE
    tmpA = new Animation(sprite->getSpriteR(), 1100, true);
    Animations.insert({"IDLE", tmpA});
    tmpA->addFrame({sf::IntRect(0,0, 401,249)});
    tmpA->addFrame({sf::IntRect(401,0, 401,249)});
    tmpA->addFrame({sf::IntRect(0,249, 401,249)});
    tmpA->addFrame({sf::IntRect(401,249, 401,249)});
    tmpA->addFrame({sf::IntRect(0,498, 401,249)});
    tmpA->addFrame({sf::IntRect(401,498, 401,249)});

    activeAnim = Animations.find("IDLE")->second;

}
void Stalker::PrepareSprite(){
    float sizeX = 401.0, sizeY = 249.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    sprite->setScale( 0.15,0.15 );
    
    Animation *tmpA;

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"up", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,249,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,249,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,498,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,498,sizeX,sizeY)});
    
 
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"right", tmpA});
    
    tmpA->addFrame({sf::IntRect(0+401,0,-sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401+401,0,-sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0+401,249,-sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401+401,249,-sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0+401,498,-sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401+401,498,-sizeX,sizeY)});
    

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"left", tmpA});
    
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,249,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,249,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,498,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,498,sizeX,sizeY)});
    

    
    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"down", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,0,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,249,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,249,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(0,498,sizeX,sizeY)});
    tmpA->addFrame({sf::IntRect(401,498,sizeX,sizeY)});

    tmpA = new Animation(sprite->getSpriteR(),1500, true);
    Animations.insert({"dead", tmpA});
    tmpA->addFrame({sf::IntRect(0,747,sizeX,sizeY)});
}

void Stalker::Update(float delta){
    Enemy::Update(delta);
    Followplayer();
}

void Stalker::Draw(double percent, double delta ){
    this->SetAnimation();
    Enemy::Draw(percent, delta); // Use this to debug draw bounding box
}


void Stalker::Followplayer(){
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

void Stalker::SetAnimation(){
    
    if(IsAlive()==true){
        Pawn::SetAnimation();
    }
}

void Stalker::Die(){
    
    activeAnim=Animations.find("dead")->second;

    setLifespan(1.5);
}