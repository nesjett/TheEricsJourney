#include "../public/Engine.h"





/***********************
 * 
 * CLASS: ENGINE
 * 
 * **********************/

Engine* Engine::pInstance = NULL;
Engine* Engine::Instance() {
    if(pInstance == NULL) { // If not created earlier, create a new instance and return it
        pInstance = new Engine();
    } 
    return pInstance;
}
Engine::Engine()
{
    //gameinstance = game::Instance();
    std::cerr << "Engine loaded()" << std::endl;
}
Engine::~Engine(){

}
sf::RenderWindow &Engine::CreateApp(sf::VideoMode vm, string wn){
    app.create(vm, wn);
    return app;
}








/***********************
 * 
 * CLASS: SPRITE
 * 
 * **********************/
SSprite::SSprite(string path){
    eng = Engine::Instance();
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error cargando la imagen sprites.png" << std::endl;
        exit(0);
    }
    //Create spriteSheet from texture
    sfsprite.setTexture(texture);

    //Set centroid
    sfsprite.setOrigin(75 / 2, 75 / 2);
    //Cut desired area from texture
    sfsprite.setTextureRect(sf::IntRect(3 * 85, 0 * 75, 75, 75));
}
SSprite::SSprite(){
    eng = Engine::Instance();
    std::cout << "SPRITE CREATED -------------" << std::endl;
}

// TODO: Create supercharge for Draw(Actor actor) so we only pass an object
/// Draw with interpolation
sf::Vector2f SSprite::Draw(sf::Vector2f location, sf::Vector2f location_prev, double percent){
    float cX = location.x; // Current X
    float oX = location_prev.x; // Old X

    float cY = location.y; // Current Y
    float oY = location_prev.y; // Old Y

    float x = (cX-oX) * percent + oX;
    float y = (cY-oY) * percent + oY;

    this->setPosition(x,y);
    eng->getApp().draw(sfsprite);

    return sf::Vector2f(x,y);
}

void SSprite::setPosition(double x, double y){
    sfsprite.setPosition(x, y);
}

void SSprite::setRotation(double angle){
    sfsprite.setRotation(angle);
}

void SSprite::setOrigin(double x, double y){
    sfsprite.setOrigin(x, y);
}
void SSprite::setTextureRect(double xx, double xy, double yx, double yy){
    sfsprite.setTextureRect(sf::IntRect(xx, yx, yx, yy));
}
void SSprite::setScale(double x, double y){
    sfsprite.setScale(x, y);
}

SSprite::~SSprite(){
 
}





/***********************
 * 
 * CLASS: ANIMATION
 * 
 * **********************/

Animation::Animation(sf::Sprite &target) : target(target) { 
    progress = totalLength = 0.0;
}
Animation::~Animation(){

}

void Animation::addFrame(AnimFrame&& frame) {
    totalLength += frame.duration; 
    frames.push_back(std::move(frame)); 
}
void Animation::update(double elapsed) {
    progress += elapsed;
    double p = progress;
    for(size_t i = 0; i < frames.size(); i++) {
        p -= frames[i].duration;  

        // if we have progressed OR if we're on the last frame, apply and stop.
        if (p <= 0.0 || &(frames[i]) == &frames.back())
        {
            target.setTextureRect(frames[i].rect);  
            if(&(frames[i]) == &frames.back()){
                progress = 0.0;
            }
            break; // we found our frame
        }
        // We check if p has some time left at the end of the animation...
        /*if (p > 0.0 && &(frames[i]) == &(frames.back())) {
            i = 0;    // start over from the beginning
            continue; // break off the loop and start where i is
        }*/
    }
}