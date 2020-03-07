#pragma once
#include <Actor.h>


class Projectile: public Actor {
    public:
        Projectile();

        string texture_file;
        sf::Sprite sprite;

        Vector2f direction;
        float movementSpeed;

        // Adds movement to the desired direction
        void UpdateMovement(); 

        sf::CircleShape bala;

        void Update(float delta);

        void Draw(sf::RenderWindow &window);

    protected:
        Clock cD, cInterp, cMov;
        void PrepareSprite();
};