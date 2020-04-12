#include <tinyxml2.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <list>
#include <Engine.h>
#include <Tile.h>

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
        list<Tile*> getActors();
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
        string nombreCapaColisiones;
        string nombreCapaObjetos;
        string nombreCapaPuertas;
        int num_layers;
        int tamMapaX, tamMapaY, tamTileX, tamTileY;
        sf::Event* evento;
        Engine* eng;
        void cargaMapa();
};