#include "../public/Enemy.h"
#include "../public/AudioManager.h"

#include <game.h>

Enemy::Enemy() : Pawn(){ // Use this to call to parent's contructor first
    Targetted = false;
    PrepareMarker();
}

void Enemy::PrepareMarker(){
    TargetMarker = new SSprite("./resources/target.png");
    TargetMarker->setScale(1.0f,1.0f); // 0.4 is the marker texture scale
}

void Enemy::Update(float delta){
    //std::cout << "Iniciamos UPDATE()" << std::endl;
    Pawn::Update(delta);
    
}

void Enemy::Draw(double percent, double delta ){
    if(Targetted) {
        float offsetx = TargetMarker->getSpriteR().getLocalBounds().width/2; // 0.4 is the marker texture scale
        float offsety = 10; // 0.4 is the marker texture scale
        TargetMarker->setPosition(this->getInterpolatedPos().x-offsetx, this->getInterpolatedPos().y-offsety);
        TargetMarker->Draw();
    }
    game *gi = game::Instance();

    Pawn::Draw(percent, delta);

    std::list<int>::iterator it;
    // Draw hit text data
   /* for (TText txt : HitText) {
        // TODO: SHould create a child class from sf::Text for adding Draw() and handle lifetime better than here
        if(gi->getTime() <= txt.getDeathTime()) {
            txt.Draw();
        } 
    }*/
    for (auto it = HitText.begin(); it != HitText.end(); it++) {
        // Notice that the iterator is decremented after it is passed 
		// to erase() but before erase() is executed 
        if(gi->getTime() <= it->getDeathTime()) {
            it->Draw(delta);
        } else {
            HitText.erase(it--);
        }
	}

}

void Enemy::Die(){
    for(int i = 0; i < 8; i++){
        game::Instance()->SpawnEmitterAtLocation(10, Vector2f(getActorLocation().x+rand() % 220 + (-110), getActorLocation().y+rand() % 20 + (-10)), Vector2f(0.f,0.f));
    }
    Pawn::Die();
}

void Enemy::TakeDamage(float damage, Actor* dmgCauser, string damage_type){
    std::cout << "Damage taken!" << std::endl; 
    if(health_Current > 0){ // Only apply damage if the enemy is alive.
        if(rand() % 100 > 85) { // 15% chances of critic
            health_Current-=damage*3;
            HitText.push_back(TText("Critico!", Vector2f(this->getActorLocation().x+rand() % 20 + (-10), this->getActorLocation().y-20.f) ,1.25));
        } else {
            health_Current-=damage;
            HitText.push_back(TText("+" + std::to_string((int)damage), Vector2f(this->getActorLocation().x+rand() % 20 + (-10), this->getActorLocation().y-20.f) ,1.25));
        }


        if(IsAlive() == false){
            Die();
            this->ToggleTarget(false);
            AudioManager::getInstance()->PlaySound2D("./resources/audio/enemy_die.ogg");
        } else {
            game *gi = game::Instance();
            gi->SpawnEmitterAtLocation(0, getActorLocation(), Vector2f(0.f,0.f));
            ApplyHitEffects(std::to_string((int)damage)); // Apply hit effects
            AudioManager::getInstance()->PlaySound2D("./resources/audio/enemy_hit.ogg");
        }
    }
}

void Enemy::ApplyHitEffects(string effect) {
    //HitText.push_back(TText("+" + effect, Vector2f(this->getActorLocation().x+rand() % 20 + (-10), this->getActorLocation().y-20.f) ,1.25));
}

bool Enemy::IsAlive(){
    if(health_Current > 0){
        return true;
    } else {
        return false;
    }
}

void Enemy::OnActorOverlap(Actor *otherActor){

}


// Base to implement attacks. This should be on the base class and be overriden by the different enemies
bool Enemy::Attack(){
    return true;
}

void Enemy::ToggleTarget(bool Active){
    Targetted = Active;
}