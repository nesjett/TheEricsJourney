#include <Pawn.h>

using namespace std;
using namespace sf;

class Enemy: public Pawn {
    public:
        Enemy();
        void TakeDamage(float damage, string damage_type);
        bool IsAlive(); // This should go to an interface or to parent PAWN class

        // Adds movement to the desired direction
        void UpdateMovement(); 
        bool Attack();
        void Update(float delta);
        void ActorOverlap(Actor otherActor);
};