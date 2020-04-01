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
        void Movimiento();
        void UpdateMovement(); 
        bool Attack();
        
        void ActorOverlap(Actor otherActor);


    protected:
        void PrepareSprite2();

    private:
        string texture_file2;

};