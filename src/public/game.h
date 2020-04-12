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
#include <Player.h>
#include <PlayerController.h>
#include <Fixedenemy.h>
#include <Movingenemy.h>
#include <Explosionenemy.h>

using namespace std;

class game
{
    public:
        static game* Instance();
        void init(/*char*, int*/);
        void run();
        void Actualizar();
        void Renderizado(float, float);
        int getTest() {
            return test;
        }

        /// Returns all enemies spawned in the world
        list<Enemy*> getAllEnemies();
        /// Returns all projectiles spawned in the world
        list<Projectile*> getAllProjectiles();
        bool soltada;
        Player* getPlayerCharacter();

        void Almacenaenemy(Projectile* proj);

        long getTime() { return gameClock.getElapsedTime().asMilliseconds(); };
        Actor* boxTraceByObjectType(FloatRect rect, ObjectType type);
        sf::Clock gameClock;

    protected:
        game();
        game(const game &);
        game &operator= (const game &);
        virtual ~game();

    private:
        static game* pInstance;
        Engine* eng;
        int test = 1;
        int largo = 1080;
        int alto = 720;
        list<Actor*> actors;

        sf::Event tecla;
        bool estadoJuego;
        Menu* menu;
        vector<Mapa*> vMapas;
        int mapaActual;
        Player *jugador;
        PlayerController* ControladorJugador;
        void InicializaNivel();
};

#endif // GAME_H


