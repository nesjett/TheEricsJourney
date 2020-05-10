#pragma once
#include <Controller.h>
#include <Player.h>
#include <Enemy.h>
#include <Projectile.h>

#include <SFML/Graphics.hpp>
#include <list>

class PlayerController:  public Controller{

    public:
        PlayerController(Player* jugador);
        void Update(sf::Event event);
        void Mover();
        void setPlayer(Player* jugador);
        void ImprovesAttack();
        void Frenar();
        void MejorarCadencia(float mej);
        void MejorarMovimiento(float mejMov);
        void IncreaseHealth();
        float getCurrentHealth();
        float getMaxHealth();
        void setGodMode(bool god);
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