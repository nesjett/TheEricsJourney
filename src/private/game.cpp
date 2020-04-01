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
}






//bucle del juego
void game::run(){

    /***********************************
     * TEST Actors, pawns and projectiles
     ***********************************/
    Pawn *enemyTest = new Pawn();
    actors.push_back(enemyTest);
    //enemyTest->setTargetLocation(Vector2f(500,400));
    Player *jugador = new Player();
    actors.push_back(jugador);

    Fixedenemy *enemyfijo = new Fixedenemy();
    actors.push_back(enemyfijo);

    Movingenemy *enemymove = new Movingenemy();
    actors.push_back(enemymove);
    enemymove->setActorLocation(Vector2f(240.0, 520.0));

    Movingenemy *enemymove2 = new Movingenemy();
    actors.push_back(enemymove2);
    enemymove2->setActorLocation(Vector2f(240.0, 520.0));

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
                    jugador->direction = Vector2f(1.0,0.0); // MOverse hacia la derecha
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
                    jugador->direction = Vector2f(-1.0,0.0); // Moverse hacia la izquierda
                }
                
                std::cout << "Tecla pulsada: " << tecla.key.code << std::endl;
            }
        }

        //Enemy movement and shot
        enemyfijo->Shot(projTest,jugador);
        
        enemymove->Linealmove_y(220.0,520.0);
        enemymove2->Linealmove_x(240.0,520.0);

        
        //enemymove->direction = Vector2f(0.0,-1.0);
        // TODO: This loops should be inside the gamestate.cpp 
        double delta = clock.getElapsedTime().asMilliseconds() - lastUpdate;


        // DRAW LOOP 
        double tup = delta / UPDATE_INTERVAL; // Parenthesis very important for a proper calculation! DON'T REMOVE
        double percentTick = min(1.0, tup);
        //std::cout << "Percent: " << percentTick << std::endl;
        //std::cout << "tup: " << tup << " delta: " << delta << " update_interval: " << UPDATE_INTERVAL << std::endl;

        eng->getApp().clear(); // CLear last frame drawings

        for (Actor *actor : actors) {
            actor->Draw(percentTick, delta);
        }
        eng->getApp().display();


        // UPDATE LOOP
        if(delta > UPDATE_INTERVAL){
            //std::cout << "GameUpdate() " << std::endl;
            
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
            lastUpdate = clock.getElapsedTime().asMilliseconds();
        }
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
