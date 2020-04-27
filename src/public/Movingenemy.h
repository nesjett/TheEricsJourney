#pragma once
#include <Enemy.h>
#include <Projectile.h>
#include <Player.h>
#include "game.h"
using namespace std;
using namespace sf;

class Movingenemy: public Enemy{
    public:
        Movingenemy();
        void Init();
        float enemydirection_y;
        float enemydirection_x;
        void Linealmove(Vector2f pos1, Vector2f pos2);

        bool Attack();
        void Update(float delta);
        void Draw(double percent, double delta );
        void Prepara(Vector2f inicio, Vector2f final);

        Vector2f x;
        Vector2f y;

        sf::Clock relojMark;
 
    private:
        string texture_file;
};