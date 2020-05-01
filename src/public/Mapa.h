#pragma once

#include <tinyxml2.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <list>
#include <Engine.h>
#include <Tile.h>
#include <Enemy.h>

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
        Tile* getPuerta();

    protected:

    private:
        string nombreMapa;
        XMLElement *mapa;
        vector<Sprite*> vectorPintar;
        vector<Sprite> vectorPintar2;
        vector<int> vPosX;
        vector<int> vPosY;
        vector<Tile*> vTiles;
        vector<Tile*> vPuertas;
        vector<Enemy*> vEnemigos;

        //Nombre de las capas en los mapa Tiled
        string nombreCapaColisiones = "colisiones";
        string nombreCapaObjetos = "objetos";
        string nombreCapaPuertas = "puerta";
        string nombreCapaEnemigos1 = "enemigos1";
        string nombreCapaEnemigos2 = "enemigos2";
        string nombreCapaEnemigos3 = "enemigos3";
        string nombreCapaSuelo = "suelo";


        int num_layers;
        int tamMapaX, tamMapaY, tamTileX, tamTileY;
        sf::Event* evento;
        Engine* eng;
        void cargaMapa();
};