#pragma once
#include <Actor.h>
#include <Projectile.h>


class Almendra: public Projectile {
    public:
        Almendra();
        Almendra(sf::Vector2f, sf::Vector2f);
        ~Almendra();

        void Update(float delta);
        void Init();

        void OnActorOverlap(Actor *otherActor);

    protected:
    private:

};