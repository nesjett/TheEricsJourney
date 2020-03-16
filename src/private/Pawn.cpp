#include "../public/Pawn.h"


Pawn::Pawn() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/zombie_male_idle.png";

    direction = Vector2f(0.f, 0.f); // Initially It has no direction

    health_MAX = 100.0f;
    health_Current = health_MAX; // Init health

    damage_Base = 15.0f;
    damage_Multiplier = 0.0f; 

    movementSpeed = 2.0f;

    faction = enemy; // By default we set the faction to enemy, just for easy of use

    setActorLocation(Vector2f(250.0, 120.0)); // PLace actor somewhere in the map

    PrepareSprite();
}

void Pawn::PrepareSprite(){
    float scale = 0.4;
    float sizeX = 430.0, sizeY = 519.0;
    float offsetX = sizeX / 2.0;
    float offsetY = sizeY / 2.0;

    sprite = new SSprite(texture_file);
    sprite->setOrigin(offsetX, offsetY);
    sprite->setTextureRect( 0, 0, sizeX*scale, sizeY*scale );

    sprite->setScale(scale,scale);
    //sprite->setPosition(getActorLocation().x, getActorLocation().y);
    
    double playrate = 5000.0;
    

    //Rect<int> t = sprite->getSprite().getTextureRect();
    Rect<float> bb = sprite->getSprite().getLocalBounds();
    //bb.left = bb.left-offsetX;
    //bb.top = bb.top-offsetY;

    setBoundingBox( Rect<float>( getActorLocation().x-offsetX, getActorLocation().y-offsetY, bb.width, bb.height ) ); // make the actor bounds be the same as the sprite used here.

    animation = new Animation(sprite->getSpriteR());
    animation->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(430,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(860,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(1290,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(1720,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(2150,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(2580,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(3010,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(3440,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(3870,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(4300,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(4730,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(5160,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(5590,0,sizeX,sizeY), playrate});
    animation->addFrame({sf::IntRect(6020,0,sizeX,sizeY), playrate});
}


void Pawn::Update(float delta){
    std::cout << "Iniciamos UPDATE()" << std::endl;
    /*if(cInterp.getElapsedTime().asMilliseconds() >= 1000/15){
        UpdateMovement();
        cInterp.restart();
    }*/

    /*game& gi = *game::Instance();
    std::cout << gi.getWindow().isOpen() << std::endl;
    while (gi.getWindow().isOpen()) {
        gi.getWindow().draw(bala);
        //std::cout << "PINTANDO!!" << std::endl;
    }*/
}

// TODO: Use delta time and interpolation
void Pawn::UpdateMovement(){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float d = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    std::cout << "Movement dir: " << r << ":" << d << std::endl; 

    //direction.x = r;
    //direction.y = d;

    moveTo(Vector2f(r, d));
}

void Pawn::Draw(double percent, double delta ){
    animation->update(delta);

    Vector2f currentLoc = sprite->Draw(location, location_prev, percent); // Location of sprite during interpolation

    sf::Rect<float> bb = getBoundingBox();
    sf::RectangleShape rect( Vector2f(bb.width,bb.height) );

    // Show actor bounding box
    rect.setPosition(bb.left,bb.top);
    rect.setFillColor(sf::Color(0,0,0,0));
    rect.setOutlineThickness(1.3);
    rect.setOutlineColor(sf::Color(250, 0, 0));

    // Show actor location
    sf::CircleShape circ( 6.0, 10.0 );
    circ.setPosition(currentLoc.x-3,currentLoc.y-3);
    circ.setFillColor(sf::Color(0,250,0));
    circ.setOutlineColor(sf::Color(0, 250, 0));
    
    Engine *eng = Engine::Instance();
    eng->getApp().draw(rect);
    eng->getApp().draw(circ);

}

void Pawn::ActorOverlap(Actor otherActor){

}


void Pawn::TakeDamage(float damage, string damage_type){
    std::cout << "Damage taken!" << std::endl; 
    if(health_Current > 0){ // Only apply damage if the enemy is alive.
        health_Current-=damage;
        if(IsAlive() == false){
            Die();
        } else {
            ApplyHitEffects(damage_type); // Apply hit effects
        }
    }
}

bool Pawn::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void Pawn::Die(){
    std::cout << "Enemy died!" << std::endl; 
}

void Pawn::ApplyHitEffects(string damage_type){
    std::cout << "Applying effect:" << damage_type << std::endl; 
}

// Base to implement attacks. This should be on the base class and be overriden by the different enemies
bool Pawn::Attack(){
    return true;
}

