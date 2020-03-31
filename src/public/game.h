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
#include <Enemy.h>
#include <Projectile.h>
#include <Player.h>
#include <PlayerController.h>

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

    protected:
        game();
        game(const game &);
        game &operator= (const game &);
        bool soltada;
        virtual ~game();

    private:
        static game* pInstance;
        Engine* eng;
        //sf::RenderWindow &app;
        int test = 1;
        int largo = 1080;
        int alto = 720;
        list<Actor*> actors;
        PlayerController* ControladorJugador;
        sf::Event tecla;
        
};

#endif // GAME_H


