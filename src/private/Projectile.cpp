#include "../public/Projectile.h"

#include <iostream>

Projectile::Projectile() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Projectile spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    direction = Vector2f(1.f, 1.f); // Initially It has no direction

    movementSpeed = 0.2;
    
    //bala = sf::CircleShape(125);
    //bala.setFillColor(sf::Color::Green);
    //bala.setPosition(250.f,150.f);

    //PrepareSprite();
    Init();
}
void Projectile::Init(){
    if (!tex.loadFromFile(texture_file)) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    //Y creo el spritesheet a partir de la imagen anterior
    sprite.setTexture(tex);

    //Le pongo el centroide donde corresponde
    sprite.setOrigin(75 / 2, 75 / 2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(3 * 85, 0 * 75, 75, 75));

    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(120, 240);

    //Escala por defecto
    sprite.setScale(1, 1);

    sprite.setRotation(90);

    std::cout << "Terminamos INIT()" << std::endl;
}



void Projectile::Update(float delta){
    //std::cout << "Iniciamos UPDATE(): " << delta << std::endl;
    float x = movementSpeed*direction.x*delta;
    float y = movementSpeed*direction.y*delta;
    x = getActorLocation().x + x;
    y = getActorLocation().y + y;
    if(x > 700) { x = 0; y = 0; } // reset position for testing
    setActorLocation(Vector2f(x,y));
    
    //sprite.setPosition(x,y);
}

// TODO: Use delta time and interpolation
void Projectile::UpdateMovement(){
    float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float d = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    std::cout << "Movement dir: " << r << ":" << d << std::endl; 

    direction.x = r;
    direction.y = d;

    sprite.setPosition(r, d);
}

void Projectile::Draw(sf::RenderWindow &window, float percent){
    //Actor::Draw();
    float cX = this->getActorLocation().x;
    float oX = this->location_prev.x;

    float cY = this->getActorLocation().y;
    float oY = this->location_prev.y;

    //float x = (cX-oX)* percent +1;
    //float y = (cY-oY)* percent +1;
    float x = oX + percent * (cX - oX);

    sprite.setPosition(x,120);
    window.draw(sprite);
}


