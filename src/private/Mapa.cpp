#include "../public/Mapa.h"
#include "../public/Movingenemy.h"
#include "../public/Explosionenemy.h"
#include "../public/Fixedenemy.h"
#include "../public/Stalker.h"

using namespace std;

Mapa::Mapa(string nombre)
{   
    nombreMapa = nombre;
    eng = Engine::Instance();
    cargaMapa();
}

Mapa::~Mapa()
{
    //delete mapa;
}

void Mapa::cargaMapa()
{
    XMLDocument documento;
    nombreMapa = "./resources/maps/" + nombreMapa;
    if(!documento.LoadFile(nombreMapa.c_str()))
        //cout << "Error leyendo el mapa." << endl;

    mapa = documento.FirstChildElement("map");

    mapa->QueryAttribute("height", &tamMapaX);
    mapa->QueryAttribute("width", &tamMapaY);
    mapa->QueryAttribute("tilewidth", &tamTileX);
    mapa->QueryAttribute("tileheight", &tamTileY);

    float sierra, movX, movY;
    XMLElement* propiedades = mapa->FirstChildElement("properties");
    if(propiedades)
    {
        XMLElement* propiedad = propiedades->FirstChildElement("property");
        while(propiedad)
        {
            if(strcmp(propiedad->Attribute("name"), strPropiedadSierra.c_str()) == 0)
            {
                sierra = stof(propiedad->Attribute("value"));
            }
            if(strcmp(propiedad->Attribute("name"), strPropiedadMovEnemyX.c_str()) == 0)
            {
                movX = stof(propiedad->Attribute("value"));
            }
            if(strcmp(propiedad->Attribute("name"), strPropiedadMovEnemyY.c_str()) == 0)
            {
                movY = stof(propiedad->Attribute("value"));
            }
            propiedad = propiedad->NextSiblingElement("property");
        }
    }
    //Cargar los sprites
    int numTileset = 0;
    XMLElement* tileset = mapa->FirstChildElement("tileset");
    while(tileset){
        numTileset++;
        tileset = tileset->NextSiblingElement("tileset");
    }

    textura_fondo_ventana.loadFromFile("./resources/maps/tiles/fondoExterior.png");
    sprite_fondo_ventana.setTexture(textura_fondo_ventana);
    sprite_fondo_ventana.setPosition(-189.f, -100.f);
    vectorPintar2.push_back(sprite_fondo_ventana);

    textura_suelo.loadFromFile("./resources/maps/tiles/sueloCespedCompleto.png");
    sprite_suelo.setTexture(textura_suelo);
    sprite_suelo.setPosition(0.f, 0.f);
    vectorPintar2.push_back(sprite_suelo);

    // vector<sf::Texture*> vectorTextura;
    // vector<sf::Sprite*> vectorSprite;
    // for(int i=0; i<numTileset;i++)
    // {
    //     vectorTextura.push_back(new sf::Texture);
    //     vectorSprite.push_back(new sf::Sprite);
    // }
    string nomSprite;
    vector<string> vectorNombresSprite;
    tileset = mapa->FirstChildElement("tileset");
    XMLElement* image;
    for(int i=0; i<numTileset;i++)
    {
        image = tileset->FirstChildElement("image");
        nomSprite = image->Attribute("source");

        // vectorTextura[i]->loadFromFile("./resources/maps/" + nomSprite);

        // vectorSprite[i]->setTexture(*vectorTextura[i]);
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
    int posVEnemy = 0;
    int posVMejora = 0;
    int posVTrampas = 0;
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
                        vTiles.push_back(new Tile(vectorNombresSprite[valor-1],posX,posY,tamTileX,tamTileY,worldstatic, false));
                    }
                    if(strcmp(layer->Attribute("name"), nombreCapaObjetos.c_str()) == 0) //Objetos o trampas
                    {
                        vTiles.push_back(new Tile(vectorNombresSprite[valor-1],posX,posY,tamTileX,tamTileY,blocker, false));
                    }
                    if(strcmp(layer->Attribute("name"), strCapaPinchos.c_str()) == 0) //Objetos o trampas
                    {
                        vTrampas.push_back(new Spikes());
                        vTrampas[posVTrampas]->setActorLocation(Vector2f(posY, posX));
                        posVTrampas++;
                    }
                    if(strcmp(layer->Attribute("name"), strCapaSierra.c_str()) == 0) //Objetos o trampas
                    {
                        // if(vTrampas.size() == 1)
                        //     sierra = sierra*3;
                        vTrampas.push_back(new Saw(Vector2f(posY,posX), sierra*tamTileX));
                        posVTrampas++;
                    }
                    if(strcmp(layer->Attribute("name"), nombreCapaPuertas.c_str()) == 0) //Puertas (falta cambiarle el oType)
                    {
                        bool esPuertaSuperior = false;
                        if(posX == 50.f)
                            esPuertaSuperior = true;
                        vPuertas.push_back(new Door(Vector2f(posY,posX + 50.f), esPuertaSuperior));
                        if(esPuertaSuperior)
                        {
                            vTiles.push_back(new Tile(vectorNombresSprite[valor-1], posX,posY, tamTileX,tamTileY,worldstatic, true));
                            vTiles.push_back(new Tile(vectorNombresSprite[valor-1],posX,posY + 50.f, tamTileX,tamTileY,worldstatic, true));
                        }
                        else{
                            vTiles.push_back(new Tile(vectorNombresSprite[valor-1], posX-50.f,posY, tamTileX,tamTileY,worldstatic, true));
                            vTiles.push_back(new Tile(vectorNombresSprite[valor-1],posX-50.f,posY + 50.f, tamTileX,tamTileY,worldstatic, true));
                        }

                    }
                    if(strcmp(layer->Attribute("name"), nombreCapaEnemigos2.c_str()) == 0) //Enemigostipo1
                    {
                        vEnemigos.push_back(new Movingenemy());
                        dynamic_cast<Movingenemy*>(vEnemigos[posVEnemy])->Prepara(Vector2f(posY + tamTileY/2.f ,posX + tamTileX/2.f), Vector2f((movY*tamTileY) + tamTileY/2.f ,(movX*tamTileX) + tamTileX/2.f));
                        posVEnemy++;
                    }
                    if(strcmp(layer->Attribute("name"), nombreCapaEnemigos1.c_str()) == 0) //Enemigostipo1
                    {
                        vEnemigos.push_back(new Fixedenemy());
                        vEnemigos[posVEnemy]->setActorLocation(Vector2f(posY + tamTileY/2,posX + tamTileX/2));
                        posVEnemy++;
                    }
                    if(strcmp(layer->Attribute("name"), nombreCapaEnemigos3.c_str()) == 0) //Enemigostipo1
                    {
                        vEnemigos.push_back(new Explosionenemy());
                        vEnemigos[posVEnemy]->setActorLocation(Vector2f(posY + tamTileY/2 ,posX + tamTileX/2));
                        posVEnemy++;
                    }
                    if(strcmp(layer->Attribute("name"), nombreCapaEnemigos4.c_str()) == 0) //Enemigostipo1
                    {
                        vEnemigos.push_back(new Stalker());
                        vEnemigos[posVEnemy]->setActorLocation(Vector2f(posY + tamTileY/2 ,posX + tamTileX/2));
                        posVEnemy++;
                    }
                    if(strcmp(layer->Attribute("name"), strCapaMejoras.c_str()) == 0)
                    {
                        //Generamos distintas mejoras aleatorias en las posiciones que leemos del mapa
                        //Controlamos que el bucle no sea infinito no poniendo mas mejoras en el mapa que tipos de mejoras hay
                        int intRandom;
                        bool unica = false;
                        while(!unica)
                        {
                            unica = true;
                            intRandom = rand() % 4;
                            vector<Mejora*>::iterator itMejora;
                            for(itMejora = vMejoras.begin(); itMejora != vMejoras.end(); itMejora++)
                            {
                                if((*itMejora)->tipoMejora == (PowerUpType)intRandom)
                                {
                                    unica = false;
                                }
                            }
                        }
                        vMejoras.push_back(new Mejora((PowerUpType)intRandom));
                        vMejoras[posVMejora]->setActorLocation(Vector2f(posY + tamTileY/2 ,posX + tamTileX/2));
                        posVMejora++;
                    }
                    if(strcmp(layer->Attribute("name"), nombreCapaSuelo.c_str()) == 0)
                    {
                        // if(valor <= vectorSprite.size())
                        // {
                        //     vectorSprite[valor-1]->setPosition(posY, posX);
                        //     vectorPintar2.push_back(*vectorSprite[valor-1]);
                        //     vPosX.push_back(posX);
                        //     vPosY.push_back(posY);
                        // }
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
    // vector<Sprite>::iterator j;
    // vector<int>::iterator x = vPosX.begin();
    // vector<int>::iterator y = vPosY.begin();
    // for(j = vectorPintar2.begin(); j != vectorPintar2.end(); j++)
    // {
    //     //(*j).setOrigin(80/2,80/2);
    //     (*j).setPosition(*y,*x);
    //     x++;
    //     y++;
    // }
}

list<Actor*> Mapa::getActors()
{
    list<Tile*> listaTiles(vTiles.begin(),vTiles.end());
    list<Enemy*> listaEnemigos(vEnemigos.begin(), vEnemigos.end());
    list<Mejora*> listaMejoras(vMejoras.begin(), vMejoras.end());
    list<Trap*> listaTrampas(vTrampas.begin(), vTrampas.end());
    list<Door*> listaPuertas(vPuertas.begin(),vPuertas.end());
    list<Actor*> actores;
    //listaTiles.merge(listaEnemigos);
    for (Door *puerta : listaPuertas)
    {
        actores.push_back(puerta);
    }
    for (Tile *tile : listaTiles)
    {
        actores.push_back(tile);
    }
    for (Mejora *mejora : listaMejoras)
    {
        actores.push_back(mejora);
    }
    for (Trap *trampa : listaTrampas)
    {
        actores.push_back(trampa);
    }
    for (Enemy *enemy : listaEnemigos)
    {
        actores.push_back(enemy);
    }
    vEnemigos.erase(vEnemigos.begin(), vEnemigos.end());
    vTiles.erase(vTiles.begin(), vTiles.end());
    vPuertas.erase(vPuertas.begin(), vPuertas.end());
    vMejoras.erase(vMejoras.begin(), vMejoras.end());
    vTrampas.erase(vTrampas.begin(), vTrampas.end());
    return actores;
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
}



