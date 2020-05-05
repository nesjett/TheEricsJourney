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
        Door* getPuerta();

    protected:

    private:
        string nombreMapa;
        XMLElement *mapa;
        vector<Sprite*> vectorPintar;
        vector<Sprite> vectorPintar2;
        vector<int> vPosX;
        vector<int> vPosY;
        vector<Tile*> vTiles;
        vector<Door*> vPuertas;
        vector<Enemy*> vEnemigos;
        vector<Trap*> vTrampas;
        vector<Mejora*> vMejoras;

        //Nombre de las capas en los mapa Tiled
        string nombreCapaColisiones = "pared";
        string nombreCapaObjetos = "blocker";
        string nombreCapaPuertas = "puerta";
        string nombreCapaEnemigos1 = "enemigos1";
        string nombreCapaEnemigos2 = "enemigos2";
        string nombreCapaEnemigos3 = "enemigos3";
        string nombreCapaSuelo = "suelo";
        string strCapaPinchos = "pinchos";
        string strCapaSierra = "sierra";
        string strCapaPowerVida = "mejoraVida";
        string strCapaPowerMov = "mejoraMovimiento";
        string strCapaPowerCadencia = "mejoraCadencia";
        string strCapaPowerAtaque= "mejoraAtaque";

        int num_layers;
        int tamMapaX, tamMapaY, tamTileX, tamTileY;
        Engine* eng;
        Texture textura_fondo_ventana;
        Sprite sprite_fondo_ventana;
        void cargaMapa();
};