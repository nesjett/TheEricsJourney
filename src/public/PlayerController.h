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
        //void Update(sf::Vector2f, bool, Player*);
        void Update(sf::Keyboard::Key, bool);
        void setPlayer(Player*);
        void setLista(list<Enemy*>);
        void Attacks();
        void Frenar(sf::Keyboard::Key);

    protected:
        virtual ~PlayerController(); 
    private: 
        sf::Vector2f stop;
        Player* miJugador;
        list<Enemy*> enemyList;
        float distancia;
        sf::Clock relojAtaque;

};