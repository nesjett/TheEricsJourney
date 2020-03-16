#include "Actor.h"


Actor::Actor() {
  std::cout << "New actor created" << std::endl;
  setActorLocation(Vector2f(0.f,0.f)); 
  //setBoundingBox( sf::Rect<float>( Vector2f(0.0,0.0), Vector2f(0.0,0.0) ) ); // Init bounding box to 0
  asleep = false;
  debug = true;
}

void Actor::Init(){

}

void Actor::Update(float delta){
  // Check for collisions here in the parent?
}

void Actor::Draw(double percent, double delta ){
  
}

Actor::~Actor(){

}