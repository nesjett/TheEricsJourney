#pragma once
#include <Actor.h>
#include <Player.h>
//#include <Animation.h>
#include <math.h>
#include <Engine.h>


class Projectile: public Actor {
    public:
        Projectile();
        Projectile(sf::Vector2f, sf::Vector2f);
        ~Projectile();

        string texture_file;
        //sf::Texture tex;
        //sf::Sprite sprite;

        Vector2f direction;
        float movementSpeed;
        float damage;

        void Update(float delta);
        void Init();
        void Draw(double percent, double delta );
        void OnActorOverlap(Actor *otherActor);
        void TakeDamage(float damage, string damage_type);

    protected:
    private:

};