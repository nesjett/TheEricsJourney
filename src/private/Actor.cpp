#include "Actor.h"

#include <iostream>

Actor::Actor() {
  std::cout << "New actor created" << std::endl;
  setActorLocation(Vector2f(0.f,0.f)); 
  setBoundingBox(Vector2f(5.f,10.f));

  
}

void Actor::Init(){

}

void Actor::Update(){
  // Check for collisions here in the parent?
}

void Actor::Draw(sf::RenderWindow &window){

}

Actor::~Actor(){

}