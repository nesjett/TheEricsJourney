#include "../public/Projectile.h"

#include <iostream>

Projectile::Projectile() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Projectile spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    direction = Vector2f(0.f, 0.f); // Initially It has no direction

    movementSpeed = 2.0f;
    
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
    std::cout << "Terminamos INIT()" << std::endl;
}



void Projectile::Update(float delta){
    std::cout << "Iniciamos UPDATE()" << std::endl;
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

void Projectile::Draw(sf::RenderWindow &window){
    //Actor::Draw();
    window.draw(sprite);
}


