#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <algorithm>

#include <Engine.h>
#include <Actor.h>
#include <Pawn.h>
#include <Zombie.h>
#include <Skeleton.h>
#include <Enemy.h>
#include <Projectile.h>
#include <Menu.h>
#include <Mapa.h>

using namespace std;

class game
{
    public:
        static game* Instance();
        void init(/*char*, int*/);
        void run();
        void Actualizar();
        void Renderizado(float, float);
        void aMoverse();
        void auxiliarMov(bool, sf::Keyboard::Key);
        void plantaAbajo();
        int getTest() {
            return test;
        }

        /// Returns all enemies spawned in the world
        list<Enemy*> getAllEnemies();
        /// Returns all projectiles spawned in the world
        list<Projectile*> getAllProjectiles();

        long getTime() { return gameClock.getElapsedTime().asMilliseconds(); }

    protected:
        game();
        game(const game &);
        game &operator= (const game &);
        virtual ~game();
        
        sf::Clock gameClock;

    private:
        static game* pInstance;
        Engine* eng;
        //sf::RenderWindow &app;
        int test = 1;
        int largo = 1080;
        int alto = 720;
        list<Actor*> actors;

        sf::Event tecla;
        bool estadoJuego;
        Menu* menu;
        vector<Mapa*> vMapas;
        int mapaActual;
};

#endif // GAME_H


