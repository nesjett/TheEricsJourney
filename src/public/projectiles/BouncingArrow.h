#pragma once
#include <Actor.h>
#include <Projectile.h>


class BouncingArrow: public Projectile {
    enum ImpactDirection { wide, height, none };
    public:
        BouncingArrow();
        BouncingArrow(sf::Vector2f, sf::Vector2f);
        ~BouncingArrow();

        void Update(float delta);
        void Draw(double percent, double delta );
        void Init();
        void OnActorOverlap(Actor *otherActor, Hit Hit) override;

    protected:
        /* Max number of times it is allowed to bounce */
        int MaxBounceCount = 0;
    private:
        Actor* DirectionPrecheck(Vector2f loc, ObjectType type);
        sf::RectangleShape movementTraceDebug;
        Actor *lastDamaged;

        int BounceCount = 0; // current count of bounces

};