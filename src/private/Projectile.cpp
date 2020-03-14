#include "../public/Projectile.h"



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
    /*if (!tex.loadFromFile(texture_file)) {
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

    //sprite.setRotation(90);
    */

    sprite = new SSprite(texture_file);

    std::cout << "Terminamos INIT()" << std::endl;
}



void Projectile::Update(float delta){
    //std::cout << "Iniciamos UPDATE(): " << delta << std::endl;
    
    UpdateMovement(delta);
}


void Projectile::UpdateMovement(float delta){
    float x = movementSpeed*direction.x*delta;
    float y = movementSpeed*direction.y*delta;
    x = getActorLocation().x + x;
    y = getActorLocation().y + y;
    if( x > 700) { // reset position for testing
        setActorLocation(Vector2f(0,0), true);
    } else {
        setActorLocation(Vector2f(x,y));
    }

    // std::atan2 uses y, x signs' for quadrant signification, unlike std::atan
    // SFML's y-axis is flipped: flip our y-component
    auto angleRads = std::atan2(direction.y, -direction.x);
    auto angleDegs = angleRads * 180.0 / M_PI;
    sprite->setRotation(angleDegs);
}

void Projectile::Draw(sf::RenderWindow &window, float percent){
    //Actor::Draw();
    float cX = this->location.x; // Current X
    float oX = this->location_prev.x; // Old X

    float cY = this->location.y; // Current Y
    float oY = this->location_prev.y; // Old Y

    float x = (cX-oX) * percent + oX;
    float y = (cY-oY) * percent + oY;

    //sprite->setPosition(x,y);
    //window.draw(sprite->getSprite());
    sprite->Draw(location, location_prev, percent);
}

Projectile::~Projectile(){
    //delete sprite;
}


