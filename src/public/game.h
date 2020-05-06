#pragma once
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <memory>

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
#include <Stalker.h>
#include <Hud.h>
#include <Mejora.h>

using namespace std;

class game
{
    public:
        static game* Instance();
        void init(/*char*, int*/);
        void run();
        void Actualizar();
        void Renderizado(float, float);

        /// Returns all enemies spawned in the world
        list<Enemy*> getAllEnemies();
        /// Returns all projectiles spawned in the world
        list<Projectile*> getAllProjectiles();
        list<Enemy*> listaEnemigos;
        Player* getPlayerCharacter();
        list<Mejora*> getMejoras();
        PlayerController* getPlayerController();

        void Almacenaenemy(Projectile* proj);

        void SpawnEmitterAtLocation(int Effect, Vector2f Location, Vector2f Rot);

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
        int largo = 1920;
        int alto = 1080;

        // List of active actors to update/render
        list<Actor*> actors;
        list<Actor*> actorsPendingDelete;

        // List of active particles to render
        vector<std::unique_ptr<Cascade>> Particles;

        sf::Event tecla;
        bool estadoJuego;
        Menu* menu;
        Mapa* mapa;
        int mapaActual;
        Player *jugador;
        PlayerController* ControladorJugador;
        void InicializaNivel();
        Clock levelClock;
        list<float> pointsPerLevel;
        float lastUpdateLevelClock;
        void CondicionVictoria();
        void EndGame();
        void KillAllEnemies();
};

#endif // GAME_H


