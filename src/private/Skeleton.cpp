#include "../public/Skeleton.h"

Skeleton::Skeleton() : Pawn(){ // Use this to call to parent's contructor first
    std::cout << "Pawn spawned..." << std::endl;  

    texture_file = "./resources/Esqueletos.png";

    setActorLocation(Vector2f(280.0, 150.0));

    PrepareSprite();
}

void Skeleton::PrepareSprite(){
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
    Animations.insert({"WALK_DOWN", tmpA});
    tmpA->addFrame({sf::IntRect(0,192, sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,192,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,192,sizeX,sizeY), playrate});

    //LEFT
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"WALK_LEFT", tmpA});
    tmpA->addFrame({sf::IntRect(0,128,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,128,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,128,sizeX,sizeY), playrate});


    //RIGHT
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"WALK_RIGHT", tmpA});
    tmpA->addFrame({sf::IntRect(0,64,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,64,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(65,64,sizeX,sizeY), playrate});


    //UP
    tmpA = new Animation(sprite->getSpriteR(), true);
    Animations.insert({"WALK_UP", tmpA});
    tmpA->addFrame({sf::IntRect(0,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(32,0,sizeX,sizeY), playrate});
    tmpA->addFrame({sf::IntRect(64,0,sizeX,sizeY), playrate});
}

void Skeleton::Draw(double percent, double delta ){
    if(activeAnim) {
        activeAnim->update(delta);
    }
    Actor::Draw(percent, delta);
}