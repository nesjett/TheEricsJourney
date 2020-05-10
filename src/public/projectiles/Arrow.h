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
        void Init();
        void OnActorOverlap(Actor *otherActor);

    protected:
    private:
        Actor *lastDamaged;
};