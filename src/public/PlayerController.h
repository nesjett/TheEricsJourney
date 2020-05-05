#pragma once
#include <Controller.h>
#include <Player.h>
#include <Enemy.h>
#include <Projectile.h>

#include <SFML/Graphics.hpp>
#include <list>

class PlayerController:  public Controller{

    public:
        PlayerController(Player*, list<Enemy*>);
        void Update(sf::Event);
        void Mover(/*sf::Keyboard::Key*/sf::Event);
        void setPlayer(Player*);
        void setLista(list<Enemy*>);
        void Attacks();
        void setAttack(list<Enemy*>);
        void ImprovesAttack();
        void Frenar(/*sf::Keyboard::Key*/);
        void MejorarCadencia(float);
        void MejorarMovimiento(float);
        void IncreaseHealth();
        float getCurrentHealth();
        float getMaxHealth();
        void setGodMode(bool);

    protected:
        virtual ~PlayerController(); 
    private: 
        Player* miJugador;
        list<Enemy*> enemyList;
        float distancia;
        sf::Clock relojAtaque;
        float mejora = 1.f;
        bool Moverse = false;
        bool stop = true;
        sf::Clock *Godclock=new sf::Clock();
        bool GodMode = false;
};