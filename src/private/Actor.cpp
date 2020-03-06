#include "Actor.h"

#include <iostream>

Actor::Actor() {
  std::cout << "New actor created";
  setActorLocation(Vector2f(0.f,0.f)); 
  setBoundingBox(Vector2f(5.f,10.f));

  Init();
}

void Actor::Init(){

}

void Actor::Update(){

}

void Actor::Draw(){

}

Actor::~Actor(){

}