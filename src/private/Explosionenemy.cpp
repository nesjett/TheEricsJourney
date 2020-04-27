#include "../public/Explosionenemy.h"

Explosionenemy::Explosionenemy(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/Zombies.png";

    setActorLocation(Vector2f(100.f, 100.f));
    direction = Vector2f(0.0, -1.0);

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 0.05f;

    setActorLocation(Vector2f(340.0, 520.0));


    Init();
    PrepareSprite();

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

void Explosionenemy::PrepareSprite(){
    float sizeX = 32.0, sizeY = 64.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY); // Set anchor to center of texture rect. Now sprite is centered with real position.
    IntRect rectangle = IntRect(0, 0, sizeX, sizeY);
    sprite->setTextureRect( rectangle ); // Set the texture section we want to add to the sprite.
    
    double playrate = 1000.0;
    Animation *tmpA;

    //DOWN
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"up", tmpA});
    tmpA->addFrame({sf::IntRect(0,192, sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,192,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,192,sizeX,sizeY), playrate});

    //LEFT
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"right", tmpA});
    tmpA->addFrame({sf::IntRect(0,128,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,128,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,128,sizeX,sizeY), playrate});


    //RIGHT
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"left", tmpA});
    tmpA->addFrame({sf::IntRect(0,64,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,64,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,64,sizeX,sizeY), playrate});


    //UP
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"down", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(64,0,sizeX,sizeY), playrate});
}

void Explosionenemy::SetAnimation(){ //selecciona la animacion del mapa de animaciones dependiendo de la direccion del actor
    
    auto angleRads = std::atan2(-direction.y, direction.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    
    if((angleDegs<22.5 && angleDegs>=0) || (angleDegs>=337.5 && angleDegs<=0)){
        activeAnim=Animations.find("right")->second;
    }
    if(angleDegs<67.5 && angleDegs>=22.5){
        activeAnim=Animations.find("right")->second;
    }
    if(angleDegs<112.5 && angleDegs>=67.5){
        activeAnim=Animations.find("up")->second;
    }
    if(angleDegs<157.5 && angleDegs>=112.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<202.5 && angleDegs>=157.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<247.5 && angleDegs>=202.5){
        activeAnim=Animations.find("left")->second;
    }
    if(angleDegs<292.5 && angleDegs>=247.5){
        activeAnim=Animations.find("down")->second;
    }
    if(angleDegs<337.5 && angleDegs>=292.5){
        activeAnim=Animations.find("right")->second;
    }

    /*if(direction==Vector2f(0.0,-1.0)){
        activeAnim=Animations.find("up")->second;
    }
    if(direction==Vector2f(0.0,1.0)){
        activeAnim=Animations.find("down")->second;
    }
    if(direction==Vector2f(-1.0,0.0)){
        activeAnim=Animations.find("left")->second;
    }
    if(direction==Vector2f(1.0,0.0)){
        activeAnim=Animations.find("right")->second;
    }
    */
    
}

void Explosionenemy::Draw(double percent, double delta ){
    SetAnimation();
    Pawn::Draw(percent, delta);
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