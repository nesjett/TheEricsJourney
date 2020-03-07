#include "../public/game.h"
#include <iostream>
#include <algorithm>

#include "../public/Pawn.h"
#include "../public/Projectile.h"

#define UPDATE_INTERVAL 1000/15

game* game::pInstance = NULL;
game* game::Instance() {
    if(pInstance == NULL) { // If not created earlier, create a new instance and return it
        pInstance = new game;
    } 
    return pInstance;
}
game::game()
{

}
void game::init(/*char* nombre, int AuxMapa*/){
    
    //Creamos una ventana
    //sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
    app.create(sf::VideoMode(largo, alto), "The Eric's Journey");

    //Cargo la imagen donde reside la textura del sprite
    //sf::Texture tex;
    if (!tex.loadFromFile("resources/sprites.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    //Y creo el spritesheet a partir de la imagen anterior
    //sf::Sprite sprite(tex);
    sprite.setTexture(tex);

    //Le pongo el centroide donde corresponde
    sprite.setOrigin(75 / 2, 75 / 2);
    //Cojo el sprite que me interesa por defecto del sheet
    sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

    // Lo dispongo en el centro de la pantalla
    sprite.setPosition((largo/2), (alto/2));
    
    
    /*app.create(sf::VideoMode(largo, alto), "Practica de Julio -King's Valley 2-");
    app.setFramerateLimit(60); //Esto pa la interpolasio
    //Paco = new sprite("ufo.png", 1, 1);
    amigo = new Player("tileCompleto.png", 1, 3, 512, 530);
    //amigo->pintarJugador();
    //amigo->pinta(app, 1);
    //Mapita = new Mapa("resources/mapa1.tmx", app);
    Mapita = new Mapa(nombre, AuxMapa);
    relojDios = new sf::Clock();
    relojRe = new sf::Clock();
    relojNivel = new sf::Clock();
    ReMade=false;
    NextLevel=false;*/


    
}






//bucle del juego
void game::run(){

    /***********************************
     * TEST Actors, pawns and projectiles
     ***********************************/
    Pawn *enemyTest = new Pawn();
    actors.push_back(enemyTest);

    Projectile *projTest = new Projectile();
    actors.push_back(projTest);
    std::cout << "Actors length: " << actors.size() << std::endl;

    enemyTest->setAsleep(true);


    /***********************************
     * Game loop
     ***********************************/
    sf::Clock clock;

    sf::Int64 lastUpdate = clock.getElapsedTime().asMilliseconds();
    sf::Int64 luf = clock.getElapsedTime().asMilliseconds();

    while (app.isOpen()) {
        //Bucle de obtención de eventos
        //sf::Event event;
        while (app.pollEvent(tecla)) {

            if (tecla.type == sf::Event::Closed){
                app.close();
            }
            if (tecla.type == sf::Event::KeyPressed){
                //Escape
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    app.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
                   sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
                    //Escala por defecto
                    sprite.setScale(1, 1);
                    sprite.move(kVel, 0); 
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
                    sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
                    //Reflejo vertical
                    sprite.setScale(-1, 1);
                    sprite.move(-kVel, 0);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
                    sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
                    sprite.move(0, -kVel);  
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
                    sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
                    sprite.move(0, kVel);
                    //enemyTest->Update(0.f);
                }
                std::cout << "Tecla pulsada: " << tecla.key.code << std::endl;
            }
        }

        // TODO: This loops should be inside the gamestate.cpp 

        // UPDATE LOOP
        float delta = clock.getElapsedTime().asMilliseconds() - lastUpdate;
        if(delta > UPDATE_INTERVAL){
            //std::cout << "GameUpdate() " << std::endl;
            
            for (Actor *actor : actors) {
                if(actor->isAsleep() == false) { // Avoid updating actors that should not update right now (ex: out of window bounds,...)
                    actor->Update(delta);
                }
            }
            lastUpdate = clock.getElapsedTime().asMilliseconds();
        }


        // DRAW LOOP 
        float tup = delta / UPDATE_INTERVAL;
        float percentTick = min(1.f, tup);

        app.clear(); // CLear last frame drawings

        for (Actor *actor : actors) {
            actor->Draw(app, tup);
        }
        luf = clock.getElapsedTime().asMilliseconds();
        app.draw(sprite);
        app.display();
    }
}


game::~game() // Destructor
{
 
}
