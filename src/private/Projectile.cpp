#include "../public/Projectile.h"

#include <iostream>

Projectile::Projectile() : Actor(){ // Use this to call to parent's contructor first
    std::cout << "Projectile spawned..." << std::endl;  

    texture_file = "./resources/sprites.png";

    direction = Vector2f(0.f, 0.f); // Initially It has no direction

    movementSpeed = 2.0f;
    
    bala = sf::CircleShape(25);
    bala.setFillColor(sf::Color::Red);

    PrepareSprite();
}

void Projectile::PrepareSprite(){
    sf::Texture tex;
    if (!tex.loadFromFile(texture_file)) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    //Y creo el spritesheet a partir de la imagen anterior
    sprite.setTexture(tex);

    //Le pongo el centroide donde corresponde
    sprite.setOrigin(75 / 2, 75 / 2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

    // Lo dispongo en el centro de la pantalla
    sprite.setPosition(120, 240);

    //Escala por defecto
    sprite.setScale(1, 1);
}


void Projectile::Update(float delta){
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
    window.draw(bala);
    
}


