#pragma once
#include <Actor.h>
#include <Projectile.h>


class FireBall: public Projectile {
    public:
        FireBall();
        FireBall(sf::Vector2f, sf::Vector2f);
        ~FireBall();

        void Update(float delta);
        void Init();
        void OnActorOverlap(Actor *otherActor);

    protected:
    private:

};