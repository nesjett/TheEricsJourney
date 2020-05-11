#pragma once

#include <tinyxml2.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <list>
#include <Engine.h>
#include <Tile.h>
#include <Enemy.h>
#include <Mejora.h>
#include <traps/Spikes.h>
#include <traps/Saw.h>
#include <Door.h>

using namespace std;
using namespace tinyxml2;
using namespace sf;

class Mapa
{
    public:
        Mapa(string nombre);
        virtual ~Mapa();
        void update();
        void render();
        list<Actor*> getActors(); 

    protected:

    private:
        int num_layers;
        int tamMapaX, tamMapaY, tamTileX, tamTileY;
        Engine* eng;
        Texture textura_fondo_ventana;
        Sprite sprite_fondo_ventana;
        Texture textura_suelo;
        Sprite sprite_suelo;
        void cargaMapa(); //Lectura del .tmx

        //Leemos el mapa por capas y nos guardamos los elementos en vectores separados
        string nombreMapa;
        XMLElement *mapa;
        vector<Sprite> vectorPintar2; //Suelo y fondo: elementos no colisionables
        vector<Tile*> vTiles;
        vector<Door*> vPuertas;
        vector<Enemy*> vEnemigos;
        vector<Trap*> vTrampas;
        vector<Mejora*> vMejoras;

        //Nombre de las capas en los mapa Tiled
        string strCapaColisiones = "pared";
        string strCapaObjetos = "blocker";
        string strCapaPuertas = "puerta";
        string strCapaEnemigos1 = "enemigos1";
        string strCapaEnemigos2 = "enemigos2";
        string strCapaEnemigos3 = "enemigos3";
        string strCapaEnemigos4 = "enemigos4";
        string strCapaEnemigos5 = "boss1";
        string strCapaSuelo = "suelo";
        string strCapaPinchos = "pinchos";
        string strCapaSierra = "sierra";
        string strCapaMejoras = "mejoras";
        string strPropiedadSierra = "LongitudSierra";
        string strPropiedadMovEnemyX = "MovingEnemyFinalPosX";
        string strPropiedadMovEnemyY = "MovingEnemyFinalPosY";
};