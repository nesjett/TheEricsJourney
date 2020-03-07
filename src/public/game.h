#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class game
{
    public:
        game();
        virtual ~game();
        void init(/*char*, int*/);
        void run();
        void Actualizar();
        void Renderizado(float, float);
        void aMoverse();
        void auxiliarMov(bool, sf::Keyboard::Key);
        void plantaAbajo();
        void moverInterpolado(float);
        void mover(float, float);
        void pinta(float);
        void aMoverse();

    protected:

    private:
        sf::RenderWindow app;
        int largo = 1080;
        int alto = 720;
        //sprite *Paco;
        //Player *amigo;
        //Mapa *Mapita;

        //nuevo 19-20
        sf::Texture tex;
        sf::Sprite sprite;
        int kVel = 5;
        float futurPosx;
        float futurPosy;
        int x, y;
        float posx, posy;
        float velX=9; 
        float velY=9;
        bool mouve = false;
        float durAnim = 1000.0/6.0;
        float tFrame  = 0.0;
        //fin nuevo 19-20
        bool GodMode = false;
        sf::Clock *relojDios;
        bool ReMade = false;
        sf::Clock *relojRe;
        bool NextLevel = false;
        sf::Clock *relojNivel;
        sf::Clock relojInterpolacion;
        float AuxInter = 0.0;
        float AuxInter2 = 0.0;
        float AuxInter3 = 0.0;
        float AuxInter4 = 1000/15;
        bool arriba=false, abajo=false, _derecha=false, _izquierda=false, salto=false;
        float _vertical = 0.0, _horizontal = 0.0;
        sf::Event tecla;
        bool enviar=false;
        bool puedoMover=false;
        int VaX =0, VaY=0;
        float auxPedoX =0.0;
        bool cambiado = false;
        bool subir = false;
        
};

#endif // GAME_H


