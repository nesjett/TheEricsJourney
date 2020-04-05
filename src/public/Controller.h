#pragma once
#include <Player.h>

#include <SFML/Graphics.hpp>

class Controller{

    public:
        Controller();
        void Move(float, float);
    protected:
        virtual ~Controller(); 
    private: 
        Player* miJugador;

};