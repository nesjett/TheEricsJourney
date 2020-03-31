#include "Mapa.h"
#include <SFML/Graphics.hpp>
using namespace std;

Mapa::Mapa(string nombre)
{   
    nombreMapa = nombre;
    nombreCapaColisiones = "Pared";
    // ventanaMapa = new sf::RenderWindow(sf::VideoMode(1280, 1920), "Mapa");
    // ventanaMapa->setFramerateLimit(60);
    eng = Engine::Instance();
    cargaMapa();
}

Mapa::~Mapa()
{
    // vectorPintar.clear();
    // vectorPintar2.clear();
    // vPosX.clear();
    // vPosY.clear();
}

void Mapa::cargaMapa()
{
    XMLDocument documento;
    nombreMapa = "./resources/maps/" + nombreMapa;
    if(!documento.LoadFile(nombreMapa.c_str()))
        cout << "Error leyendo el mapa." << endl;

    mapa = documento.FirstChildElement("map");

    mapa->QueryAttribute("height", &tamMapaX);
    mapa->QueryAttribute("width", &tamMapaY);
    mapa->QueryAttribute("tilewidth", &tamTileX); //pq son mismo tamanyo
    mapa->QueryAttribute("tileheight", &tamTileY);

    //Cargar los sprites
    int numTileset = 0;
    XMLElement* tileset = mapa->FirstChildElement("tileset");
    while(tileset){
        numTileset++;
        tileset = tileset->NextSiblingElement("tileset");
    }

    vector<sf::Texture*> vectorTextura;
    vector<sf::Sprite*> vectorSprite;
    for(int i=0; i<numTileset;i++)
    {
        vectorTextura.push_back(new sf::Texture);
        vectorSprite.push_back(new sf::Sprite);
    }
    string nomSprite;
    vector<string> vectorNombresSprite;
    tileset = mapa->FirstChildElement("tileset");
    XMLElement* image;
    for(int i=0; i<numTileset;i++)
    {
        image = tileset->FirstChildElement("image");
        nomSprite = image->Attribute("source");

        vectorTextura[i]->loadFromFile("./resources/maps/" + nomSprite);

        vectorSprite[i]->setTexture(*vectorTextura[i]);
        vectorNombresSprite.push_back("./resources/maps/" + nomSprite);
        if(tileset->NextSiblingElement("tileset"))     
            tileset = tileset->NextSiblingElement("tileset");
    }

    //Cargar las capas
    num_layers = 0;
    XMLElement* layer = mapa->FirstChildElement("layer");
    while(layer){
        num_layers++;
        layer = layer->NextSiblingElement("layer");
    }


    layer = mapa->FirstChildElement("layer");
    XMLElement* tile;
    int posX = 0;
    int posY = 0;
    for(int l = 0; l < num_layers; l++)
    {   
        tile = (layer->FirstChildElement("data"))->FirstChildElement("tile");

        for(int x = 0; x < tamMapaX; x++)
        {
            for(int y = 0; y < tamMapaY; y++)
            {
                if(tile->Attribute("gid"))
                {
                    int valor = atoi(tile->Attribute("gid"));
                    if(strcmp(layer->Attribute("name"), nombreCapaColisiones.c_str()) == 0) //Elementos Colisionables
                    {
                        vTiles.push_back(new Tile(vectorNombresSprite[valor-1],posX,posY,tamTileX,tamTileY));
                    }
                    else{
                        vectorPintar2.push_back(*vectorSprite[valor-1]);
                        vPosX.push_back(posX);
                        vPosY.push_back(posY);
                    }
                }
                if(tile->NextSiblingElement("tile"))
                    tile = tile->NextSiblingElement("tile");
                posY = posY + tamTileY;
            }
            posY = 0;
            posX = posX + tamTileX;
        }
        posX = 0;
        posY = 0;
        layer = layer->NextSiblingElement("layer");
    }
    //Seteamos posiciones
    vector<Sprite>::iterator j;
    vector<int>::iterator x = vPosX.begin();
    vector<int>::iterator y = vPosY.begin();
    for(j = vectorPintar2.begin(); j != vectorPintar2.end(); j++)
    {
        //(*j).setOrigin(80/2,80/2);
        (*j).setPosition(*y,*x);
        x++;
        y++;
    }
}


void Mapa::update()
{

}
void Mapa::render()
{
    vector<Sprite>::iterator i;
    for(i = vectorPintar2.begin(); i != vectorPintar2.end(); i++)
    {
        eng->getApp().draw(*i);
    }
    vector<Tile*>::iterator j;
    for(j = vTiles.begin(); j != vTiles.end(); j++)
    {
        (*j)->Draw(5000.0,0.0);
    }
}



