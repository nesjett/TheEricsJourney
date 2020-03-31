#include "../public/game.h"



#define UPDATE_INTERVAL (1000/15.0)

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
    eng = Engine::Instance();
    eng->CreateApp(sf::VideoMode(largo, alto), "The Eric's Journey");
    //app = eng->getApp(); // NOT WORKING FOR SOME REASON

    estadoJuego = false;
    menu = Menu::getInstance();
    mapaActual = 0;
    vMapas.push_back(new Mapa("MapaNivel1.tmx"));
}






//bucle del juego
void game::run(){

    /***********************************
     * TEST Actors, pawns and projectiles
     ***********************************/
    Pawn *enemyTest = new Pawn();
    actors.push_back(enemyTest);
    //enemyTest->setTargetLocation(Vector2f(500,400));

    Projectile *projTest = new Projectile();
    actors.push_back(projTest);
    std::cout << "Actors length: " << actors.size() << std::endl;

    //enemyTest->setAsleep(true);


    /***********************************
     * Game loop
     ***********************************/
    sf::Clock clock;
    sf::Int64 lastUpdate = clock.getElapsedTime().asMilliseconds();

    while (eng->getApp().isOpen()) {
        //Bucle de obtención de eventos
        //sf::Event event;
        while (eng->getApp().pollEvent(tecla)) {

            if (tecla.type == sf::Event::Closed){
                eng->getApp().close();
            }
            if (tecla.type == sf::Event::KeyPressed){
                //Escape
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    eng->getApp().close();
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
                    enemyTest->direction = Vector2f(1.0,0.0); // MOverse hacia la derecha
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    enemyTest->direction = Vector2f(-1.0,0.0); // Moverse hacia la izquierda
                }
                
                std::cout << "Tecla pulsada: " << tecla.key.code << std::endl;
            }
            if(estadoJuego == false) //Estamos en el menu
            {
                estadoJuego = menu->update(tecla);
            }
        }

        // TODO: This loops should be inside the gamestate.cpp 
        double delta = clock.getElapsedTime().asMilliseconds() - lastUpdate;


        // DRAW LOOP 
        double tup = delta / UPDATE_INTERVAL; // Parenthesis very important for a proper calculation! DON'T REMOVE
        double percentTick = min(1.0, tup);
        //std::cout << "Percent: " << percentTick << std::endl;
        //std::cout << "tup: " << tup << " delta: " << delta << " update_interval: " << UPDATE_INTERVAL << std::endl;

        // eng->getApp().clear(); // CLear last frame drawings

        // for (Actor *actor : actors) {
        //     actor->Draw(percentTick, delta);
        // }
        // eng->getApp().display();


        // UPDATE LOOP
        if(delta > UPDATE_INTERVAL){
            //std::cout << "GameUpdate() " << std::endl;
            if(estadoJuego == true){ //Estamos jugando! ;-)
                for (Actor *actor : actors) {
                    if(actor->isAsleep() == false) { // Avoid updating actors that should not update right now (ex: out of window bounds,...)
                        actor->Update(delta);
                    }

                    // CHeck collisions. BAD PERFORMANCE! O(n^2) !!
                    // Can be improved by not checking the pairs that were already checked
                    for (Actor *test : actors) {
                        if(actor != test){
                            //std::cout << "------------ CHECKING OVERLAP ------------" << std::endl;
                            bool overlaps = actor->getBoundingBox().intersects( test->getBoundingBox() );
                            if(overlaps){
                                //std::cout << "--------------------------------- OVERLAPS! ----------------------------" << std::endl;
                                test->OnActorOverlap(actor);
                            }
                        }
                    }
                }
            }
            lastUpdate = clock.getElapsedTime().asMilliseconds();
        }
        //RENDER
        eng->getApp().clear(); 
        if(estadoJuego == false)
        {
            menu->draw();
        }
        else{
            vMapas[mapaActual]->render();
            for (Actor *actor : actors) {
                actor->Draw(percentTick, delta);
            }
        }
        eng->getApp().display();
    }
}

list<Enemy*> game::getAllEnemies(){
    list<Enemy*> tmp;
    Enemy* tmpE = NULL;
    for (Actor *actor : actors) {
        if ( static_cast<Enemy*>( actor ) ) {
            tmpE = static_cast<Enemy*>(actor);
            tmp.push_back(tmpE);
        }
    }
    return tmp;
}

list<Projectile*> game::getAllProjectiles(){
    list<Projectile*> tmp;
    Projectile* tmpE = NULL;
    for (Actor *actor : actors) {
        if ( static_cast<Projectile*>( actor ) ) {
            tmpE = static_cast<Projectile*>(actor);
            tmp.push_back(tmpE);
        }
    }
    return tmp;
}


game::~game() // Destructor
{
 
}
