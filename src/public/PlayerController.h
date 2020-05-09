#pragma once
#include <Controller.h>
#include <Player.h>
#include <Enemy.h>
#include <Projectile.h>

#include <SFML/Graphics.hpp>
#include <list>

class PlayerController:  public Controller{

    public:
        PlayerController(Player*);
        void Update(sf::Event);
        void Mover(sf::Event);
        void setPlayer(Player*);
        void ImprovesAttack();
        void Frenar();
        void MejorarCadencia(float);
        void MejorarMovimiento(float);
        void IncreaseHealth();
        float getCurrentHealth();
        float getMaxHealth();
        void setGodMode(bool);
        void ModifyDamage();
        void ModifyCritic(float cri);
        virtual ~PlayerController(); 

    protected:
        
    private: 
        Player* miJugador;
        float distancia;
        float mejora = 1.f;
        bool Moverse = false;
        bool stop = true;
        sf::Clock *Godclock=new sf::Clock();
        bool GodMode = false;
};