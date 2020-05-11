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
#include <Mejora.h>

using namespace std;
using namespace sf;

class Hud
{
    public:
        static Hud* Instance();

        //Para el jugador
        void setMaxHealth(float health);
        void setCurrentHealth(float health);
        void setPlayer(Player* player);

        void setNumMapa(int num);

        void addMejora(PowerUpType tipo);
        void resetMejoras();

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
        RectangleShape playerHealth;
        float currentHealth;
        float maxHealth;
        float height, width; //Dimensiones del rectangulo barra de vida
        float percent; //Porcentaje vidaActual/vidaTotal
        Color colorHealth100, colorHealthLess50, colorHealthLess25; //Colores de la barra de vida, actualmente solo el verde
        vector<RectangleShape*> cuadraditos; //Cuadrados que dividen la barra de vida del jugador

        //Barras de vida de los enemigos
        vector<RectangleShape*> enemyHealthBars;
        float widthEnemigo;

        //Datos de los powerups adquiridos
        float separacion = 50.f;
        Text txtHealth, txtMovSpeed, txtAttackSpeed, txtAttackMore, txtMoreDamage, txtCritAttack;
        int vecesMejora1 = 0;
        int vecesMejora2 = 0;
        int vecesMejora3 = 0;
        int vecesMejora4 = 0;
        int vecesMejora5 = 0;
        int vecesMejora6 = 0;
        Texture *tx1 = new Texture();
        Texture *tx2 = new Texture();
        Texture *tx3 = new Texture();
        Texture *tx4 = new Texture();
        Texture *tx5 = new Texture();
        Texture *tx6 = new Texture();
        vector<Sprite*> spritesMejoras;
        vector<Texture> texturasMejoras;

        //Marco de las mejoras y texto de mapa actual
        Text textoMapa;
        Texture texVentana;
        Sprite spriteVentana;
};

#endif // Hud_H


