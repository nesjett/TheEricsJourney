#pragma once
#include <Enemy.h>
#include <Projectile.h>
#include <Player.h>
#include "game.h"

using namespace std;
using namespace sf;

class Explosionenemy: public Enemy{
    public:
        Explosionenemy();
        void Init();
        bool Attack();
        void Followplayer();
        void PrepareSprite();
        void Update(float delta);
        void Draw(double percent, double delta );
        Vector2f RandomNewDir();
        //Vector2f Direccionunitaria(Vector2f pos_player,Vector2f pos);
        sf::Clock relojMark;//controls the shoting rate
        sf::Clock relojdireccion;
        sf::Clock relojPausa;
        void Die();// if he dies activates the dead animation
    protected:
    
        void SetAnimation();    


    private:
        string texture_file;
};