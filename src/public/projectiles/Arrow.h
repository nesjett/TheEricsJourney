#pragma once
#include <Actor.h>
#include <Projectile.h>


class Arrow: public Projectile {
    public:
        Arrow();
        Arrow(sf::Vector2f, sf::Vector2f);
        ~Arrow();

        void Update(float delta);
        void Init();

    protected:
    private:

};