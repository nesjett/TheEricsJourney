#pragma once
#include <Actor.h>
#include <Projectile.h>


class Rock: public Projectile {
    public:
        Rock();
        Rock(sf::Vector2f, sf::Vector2f);
        ~Rock();

        void Update(float delta);
        void Init();

    protected:
    private:

};