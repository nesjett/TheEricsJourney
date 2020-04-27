#pragma once
#ifndef HUD_H
#define HUD_H

#include <iostream>
#include <list>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <algorithm>

#include <Engine.h>
#include <Player.h>
#include <Enemy.h>

using namespace std;
using namespace sf;

class Hud
{
    public:
        static Hud* Instance();
        void setMaxHealth(float health);
        void setCurrentHealth(float health);


        void setPlayer(Player* player);
        void addEnemy(Enemy* enemy);
        void Update();
        void Draw();


    protected:
    private:
        Hud();
        virtual ~Hud();
        static Hud* pInstance;
        Engine* eng;
        Font fontHud;

        //Barra de vida del jugador
        Player* jugador;
        Text txtHealth;
        RectangleShape playerHealth;
        float currentHealth;
        float maxHealth;
        float height, width;
        float percent; //Porcentaje vidaActual/vidaTotal
        Color colorHealth100, colorHealthLess50, colorHealthLess25; 

        //Datos de los powerups adquiridos - TO DO: una vez gestionemos powerups
        Text txtPowerUpInfo;
        vector<Sprite> spritePowerUps;
        vector<Text> txtPowerUps;

        //Barras de vida de los enemigos
        vector<Enemy*> enemigos;
        vector<RectangleShape> enemyHealthBars;
};

#endif // Hud_H


