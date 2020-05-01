#include <Trap.h>

//#include <game.h>

Trap::Trap() : Actor(){ // Use this to call to parent's contructor first
    texture_file = "./resources/traps/spikes.png";

    damage_factor = 0.2;
    oType = worlddynamic;
    setActorLocation(Vector2f(0.f, 0.f)); // PLace actor somewhere in the map
    target = nullptr;

}

void Trap::PrepareSprite(){
 
}

void Trap::Update(float delta){
   Actor::Update(delta);
}

void Trap::Draw(double percent, double delta ){
    Actor::Draw(percent, delta);
}

void Trap::OnActorOverlap(Actor *otherActor){

}


