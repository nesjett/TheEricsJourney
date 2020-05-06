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

void Engine::setView(float centerY, float borderX)
{
    //vista = new sf::View(sf::FloatRect(0.f, 600.f, vm.width, vm.height));
    float posArriba = centerY - (app.getSize().y / 2);
    // if(posArriba < 0.f)
    //     posArriba = 0.f;
    if(posArriba < -100.f)
        posArriba = -100.f;
    // if(posArriba > 280.f)
    //     posArriba = 280.f;
    if(posArriba > 380.f)
        posArriba = 380.f;
    vista.reset(sf::FloatRect(borderX, posArriba, app.getSize().x, app.getSize().y));
    //vista.setViewport(sf::FloatRect(borderX, 0, 1.f, 1.f));
    app.setView(vista);
}

void Engine::resetView()
{
    vista.reset(sf::FloatRect(0.f, 0.f, app.getSize().x, app.getSize().y));
    app.setView(vista);
}








/***********************
 * 
 * CLASS: SPRITE
 * 
 * **********************/
SSprite::SSprite(string path){
    eng = Engine::Instance();
    LoadTexture(path);
    GlobalBounds = sf::FloatRect();
}

SSprite::SSprite(){
    eng = Engine::Instance();
}

// Draw at current location
sf::Vector2f SSprite::Draw(){
    eng->getApp().draw(sfsprite);
}

sf::Texture SSprite::LoadTexture(string path) {
    if (!texture.loadFromFile(path)) {
        std::cerr << "Error cargando la imagen" << path << std::endl;
        exit(0);
    }
    TextPath = path;
    sfsprite.setTexture(texture);
    GlobalBounds = sf::FloatRect();
    return texture;
}

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

sf::FloatRect SSprite::getGlobalBounds() {
    
    return sfsprite.getGlobalBounds();
}

sf::FloatRect SSprite::getBounds() {
    sf::FloatRect current = sfsprite.getGlobalBounds();
    if(GlobalBounds.width == 0.f) {
        return current;
    }
    /*if(TextPath == "./resources/projectiles/fireball-short.png") {
        int i = 0;
    }*/
    //GlobalBounds.width = current.width;
    //GlobalBounds.height = current.height;
    float top = (current.height * (GlobalBounds.height/current.height) ) /2;
    float left = (current.width *  (GlobalBounds.width/current.width) ) / 2;

    current.top = current.top + top + GlobalBounds.height/2; // TODO: For some reason seems not to properly center vertically
    current.left = current.left + left;
    current.width = GlobalBounds.width;
    current.height = GlobalBounds.height;
    return current;
}


/*/////////////////////////////////////////////////////////
\brief set the position of the object

This function completely overwrites the previous position.
See the move function to apply an offset based on the previous position instead.
The default position of a transformable object is (0, 0).

\param x X coordinate of the new position
\param y Y coordinate of the new position

\see move, getPosition

/////////////////////////////////////////////////////////*/
void SSprite::setPosition(double x, double y){
    sfsprite.setPosition(x, y);
}


/*/////////////////////////////////////////////////////////
\brief set the orientation of the object

This function completely overwrites the previous rotation.
See the rotate function to add an angle based on the previous rotation instead.
The default rotation of a transformable object is 0.

\param angle New rotation, in degrees

\see rotate, getRotation

/////////////////////////////////////////////////////////*/
void SSprite::setRotation(double angle){
    sfsprite.setRotation(angle);
}

/*/////////////////////////////////////////////////////////
\brief set the local origin of the object

The origin of an object defines the center point for
all transformations (position, scale, rotation).
The coordinates of this point must be relative to the
top-left corner of the object, and ignore all
transformations (position, scale, rotation).
The default origin of a transformable object is (0, 0).

\param x X coordinate of the new origin
\param y Y coordinate of the new origin

\see getOrigin

/////////////////////////////////////////////////////////*/
void SSprite::setOrigin(double x, double y){
    sfsprite.setOrigin(x, y);
}

/*/////////////////////////////////////////////////////////
\brief Set the sub-rectangle of the texture that the sprite will display

The texture rect is useful when you don't want to display
the whole texture, but rather a part of it.
By default, the texture rect covers the entire texture.

\param x, y, width, height
\

\see getTextureRect, setTexture

/////////////////////////////////////////////////////////*/
void SSprite::setTextureRect(double x, double y, double w, double h){
    sfsprite.setTextureRect(sf::IntRect(x, y, w, h));
}

/*/////////////////////////////////////////////////////////
\brief Set the sub-rectangle of the texture that the sprite will display

The texture rect is useful when you don't want to display
the whole texture, but rather a part of it.
By default, the texture rect covers the entire texture.

\param Rect rectangle to crop the texture

\see getTextureRect, setTexture

/////////////////////////////////////////////////////////*/
void SSprite::setTextureRect(sf::IntRect rect){
    sfsprite.setTextureRect(rect);
}

/*/////////////////////////////////////////////////////////
\brief set the scale factors of the object

This function completely overwrites the previous scale.
See the scale function to add a factor based on the previous scale instead.
The default scale of a transformable object is (1, 1).

\param factorX New horizontal scale factor
\param factorY New vertical scale factor

\see scale, getScale

/////////////////////////////////////////////////////////*/
void SSprite::setScale(double x, double y){
    sfsprite.setScale(x, y);
}

// Based on the sprite global bounds, readjust the bounding box to a custom one, relative to the global ones.
sf::FloatRect SSprite::setBounds(float newScale) {
    sf::FloatRect current = sfsprite.getGlobalBounds();
    GlobalBounds.height = current.height * newScale;
    GlobalBounds.width = current.width * newScale;
    GlobalBounds.top = 0.f; // Set to 0 because this changes over time. DInamically calculated in getBOunds()
    GlobalBounds.left = 0.f; // Set to 0 because this changes over time.  DInamically calculated in getBOunds()
    return GlobalBounds;
}

SSprite::~SSprite(){
 
}






/***********************
 * 
 * CLASS: ANIMATION
 * 
 * **********************/

Animation::Animation(sf::Sprite &target, int length) : target(target) { 
    progress = 0;
    totalLength = 0.0;
    duration = length;
    totalProgress = 0;
    currentFrame = 0;
    loop = false;
}
Animation::Animation(sf::Sprite &target, int length, bool looping) : target(target) { 
    progress = 0;
    totalLength = 0.0;
    duration = length;
    totalProgress = 0;
    currentFrame = 0;
    loop = looping;
}
Animation::~Animation(){

}

void Animation::Reset() {
    progress = 0;
    totalProgress = 0;
    currentFrame = 0;
}

/*/////////////////////////////////////////////////////////
\brief set a new frame to the animation array

\param frame FRAME struct to add

/////////////////////////////////////////////////////////*/
void Animation::addFrame(AnimFrame&& frame) {
    totalLength += frame.duration; 
    frames.push_back(std::move(frame)); 
}
int Animation::update(double elapsed) {
    progress += elapsed;
    totalProgress += elapsed;
    //double p = progress;

    if(progress/1.f >= duration/frames.size()) {
        currentFrame++;
        if(!loop && currentFrame/1.f >= frames.size()){
            progress = 0;
            return 0;
        }
        if(currentFrame/1.f >= frames.size()){
            currentFrame = 0;
        }
        target.setTextureRect(frames[currentFrame].rect);
        progress = 0;
    }

    return duration - totalProgress;
}








/***********************
 * 
 * CLASS: CASCADE
 * 
 * **********************/
// TODO: Now we are using this class RAW as a particle emitter, but this should be just one component of many that composes a emitter.

Cascade::Cascade(sf::Vector2f loc) : SSprite() { 
    this->setPosition(loc.x, loc.y);
    AutoDestroy = true;
    Lifetime = 1.f;
    PendingDelete = false;
}

Cascade::Cascade(){
    AutoDestroy = true;
    Lifetime = 1.f;
    PendingDelete = false;
}

Cascade::~Cascade(){

}

void Cascade::Draw(double delta) {
    int remaining = 0;
    if(Anim) {
        remaining = Anim->update(delta);
        if(remaining <= 0) {
            PendingDelete = true;
        }
    }
    SSprite::Draw();
}
int Cascade::GetRemainingLife() {
    return Lifetime - LifeCounter.getElapsedTime().asMilliseconds();
}
void Cascade::SetLifetime(int time) { Lifetime = time; }
void Cascade::SetAuto(bool Auto) { AutoDestroy = Auto; };