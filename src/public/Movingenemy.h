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
        void Linealmove_y(float pos1, float pos2);
        void Linealmove_x(float pos1, float pos2);
        bool Attack();
        void Update(float delta);
        void Draw(double percent, double delta );
        
        sf::Clock relojMark;
 
    private:
        string texture_file;
};