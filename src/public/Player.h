#pragma once
#include <Pawn.h>
#include <Enemy.h>
#include <list>
#include <Hud.h>

using namespace std;
using namespace sf;

class Player:  public Pawn{
    public:
        Player();
        void TakeDamage(float damage, Actor* dmgCauser, string damage_type);
        bool IsAlive(); // This should go to an interface or to parent PAWN class
        void Init();
        // Adds movement to the desired direction
        void Movimiento(sf::Vector2f);
        void setDirection(float, float);
        sf::Vector2f getDirection();
        void UpdateMovement(); 
        void Attack(list<Enemy*>);
        void Update(float delta);
        void ActorOverlap(Actor otherActor);
        void Draw(double percent, double delta);
        void setHealthMax(float);
        void setCurrentH(float);
        float getCurrentHealth();
        float getMaxHealth();

    protected:
        void PrepareSprite();

    private:
        string texture_file;
        
};