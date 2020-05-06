#pragma once
#include <Actor.h>
#include <Projectile.h>


class Arrow: public Projectile {
    enum ImpactDirection { wide, height, none };
    public:
        Arrow();
        Arrow(sf::Vector2f, sf::Vector2f);
        ~Arrow();

        void Update(float delta);
        void Draw(double percent, double delta );
        void Init();
        void OnActorOverlap(Actor *otherActor);

    protected:
    private:
        Actor *lastCollided;
        ImpactDirection LastImpact = none;
        int creationTime;
        sf::Clock timer;
        Actor* DirectionPrecheck(Vector2f InitialLocation, Vector2f FinalLocation, ObjectType type);
        sf::RectangleShape movementTraceDebug;
        Actor *lastDamaged;

};