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
    list<Tile*> mapColisionables = vMapas[mapaActual]->getActors();
    for (Tile *tile : mapColisionables)
    {
        actors.push_back(tile);
    }
    Pawn *enemyTest = new Pawn();
    actors.push_back(enemyTest);
    //enemyTest->setTargetLocation(Vector2f(500,400));
    Player *jugador = new Player();
    actors.push_back(jugador);

    Fixedenemy *enemyfijo = new Fixedenemy();
    actors.push_back(enemyfijo);

    /*Projectile *projTest = new Projectile();
    actors.push_back(projTest);*/

    std::cout << "Actors length: " << actors.size() << std::endl;
    //enemyTest->setAsleep(true);
    ControladorJugador = new PlayerController(jugador);

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
                soltada = false;
                ControladorJugador->Update(tecla.key.code, soltada);
                
                std::cout << "Tecla pulsada: " << tecla.key.code << std::endl;
            }
            if (tecla.type == sf::Event::KeyReleased){
                enemyTest->direction = Vector2f(0.0, 0.0);
                soltada = true;
                ControladorJugador->Update(tecla.key.code, soltada);
                
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

Player* game::getPlayerCharacter(){
    Player* tmp;
    for (Actor *actor : actors) {
        if ( dynamic_cast<Player*>( actor ) ) {
            tmp = dynamic_cast<Player*>(actor);
            break;
       }
    }
    return tmp;
}

void game::Almacenaenemy(Projectile* proj){
    actors.push_back(proj); 
    
}

game::~game() // Destructor
{
 
}
