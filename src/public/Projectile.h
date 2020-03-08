#pragma once
#include <Actor.h>
#include <Animation.h>
#include <math.h>


class Projectile: public Actor {
    public:
        Projectile();

        string texture_file;
        sf::Texture tex;
        sf::Sprite sprite;

        Vector2f direction;
        float movementSpeed;

        // Adds movement to the desired direction
        void UpdateMovement(float delta); 

        //sf::CircleShape bala;

        void Update(float delta);
        void Init();
        void Draw(sf::RenderWindow &window, float percent);

    protected:
};