#pragma once
#include <Enemy.h>
#include <Projectile.h>
#include <Player.h>
#include "game.h"

using namespace std;
using namespace sf;

class Stalker: public Enemy{
    public:
        Stalker();
        void Init();
        bool Attack();
        void Followplayer();
        void Update(float delta);
        void Draw(double percent, double delta );
        void PrepareSprite();
        //Vector2f Direccionunitaria(Vector2f pos_player,Vector2f pos);
        sf::Clock relojMark;//controls the shoting rate
        void Die();// if he dies activates the dead animation
    protected:
    
        void SetAnimation();

    private:
        string texture_file;
};