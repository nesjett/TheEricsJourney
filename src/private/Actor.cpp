#include "Actor.h"


Actor::Actor() {
  std::cout << "New actor created" << std::endl;
  setActorLocation(Vector2f(0.f,0.f)); 
  setBoundingBox(Vector2f(5.f,10.f));
  asleep = false;
}

void Actor::Init(){

}

void Actor::Update(float delta){
  // Check for collisions here in the parent?
}

void Actor::Draw(sf::RenderWindow &window, float percent){

}

Actor::~Actor(){

}