#pragma once
#include <Enemy.h>
#include <Projectile.h>
#include <Player.h>
#include "game.h"

using namespace std;
using namespace sf;

class Fixedenemy: public Enemy{
    public:
        Fixedenemy();
        void Init();
        bool Attack();

        void Update(float delta);

        sf::Clock relojMark;

    private:
        string texture_file;
};