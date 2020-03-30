#pragma once
#include <Pawn.h>

using namespace std;
using namespace sf;

class Player:  public Pawn{
    public:
        Player();
        void TakeDamage(float damage, string damage_type);
        bool IsAlive(); // This should go to an interface or to parent PAWN class
        void Init();
        // Adds movement to the desired direction
        void Movimiento(bool, sf::Keyboard::Key);
        void UpdateMovement(); 
        bool Attack();
        void Update(float delta);
        void ActorOverlap(Actor otherActor);
        void Draw(double percent, double delta);
        sf::Vector2f direction;

    protected:
        void PrepareSprite2();

    private:
        string texture_file2;
        
};