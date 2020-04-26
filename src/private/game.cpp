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
    jugador = new Player();
    InicializaNivel();
}

void game::InicializaNivel()
{
    //Limpiamos los datos de los colisionables del mapa anterior
    for (Actor *actor : actors) { 
        if(actor->getObjectType() == worldstatic)
            actor->setLifespan(0.0);
    }

    //Guardamos la puntuacion del nivel anterior
    if(estadoJuego == true) //Nos aseguramos de que lastUpdateLevelClock este inicializado
    {
        float porcentaje = (1 - (levelClock.getElapsedTime().asSeconds()-lastUpdateLevelClock)/600); //1 - minutos_transcrridos/100
        float points = porcentaje*1000000; //Puntuacion max es de 1.000.000
        pointsPerLevel.push_back(points);
    }


    if(mapaActual < 3) //HARDCODED: numero maximo de niveles es 3
    {
        //Cargamos el nivel
        string nombreMapa = "MapaNivel"+to_string(mapaActual+1)+".tmx";
        vMapas.push_back(new Mapa(nombreMapa));

        //Cargamos las colisiones del nivel
        list<Tile*> mapColisionables = vMapas[mapaActual]->getActors();
        for (Tile *tile : mapColisionables)
        {
            actors.push_back(tile);
        }

        //Protagonista set location al inicio del mapa
        jugador->setActorLocation(Vector2f(350.0,200.0));
        
        //Set vista a la primera parte del mapa
        //eng->ChangeAppView(0);

        //Epmpezamos a correr el tiempo del nivel
        lastUpdateLevelClock = levelClock.getElapsedTime().asSeconds();
    }
    else{
        //Cargamos la pantalla de puntuaciones
        estadoJuego = false;
        menu->cambiarAPantallaFinal(pointsPerLevel);
    }
}






//bucle del juego
void game::run(){

    /***********************************
     * TEST Actors, pawns and projectiles
     ***********************************/
    actors.push_back(jugador);
    jugador->setActorLocation(Vector2f(350.0,500.0));
    /*
    Fixedenemy *enemyfijo = new Fixedenemy();
    actors.push_back(enemyfijo);
    enemyfijo->setActorLocation(Vector2f(600.0,550.0));

    Movingenemy *enemymove = new Movingenemy();
    actors.push_back(enemymove);
    enemymove->Prepara(Vector2f(500.0,300.0),Vector2f(300.0,400.0));
    */
    Explosionenemy *enemyexp = new Explosionenemy();
    actors.push_back(enemyexp);
    enemyexp->setActorLocation(Vector2f(400.0,400.0));
    
    Stalker *stalker = new Stalker();
    actors.push_back(stalker);
    stalker->setActorLocation(Vector2f(400.0,400.0));
    
    
    /*Projectile *projTest = new Projectile();
    actors.push_back(projTest);*/
    listaEnemigos = getAllEnemies();
    ControladorJugador = new PlayerController(jugador, listaEnemigos);

    Pawn *enemyTest = new Pawn();
    actors.push_back(enemyTest);

    Skeleton *enemyTest2 = new Skeleton();
    actors.push_back(enemyTest2);

    Zombie *enemyTest3 = new Zombie();
    actors.push_back(enemyTest3);
    enemyTest3->setActorLocation(Vector2f(310,180));
    
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
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
                    ControladorJugador->MejorarCadencia(0.9);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::V)){
                    ControladorJugador->MejorarMovimiento(1.08);
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                    ControladorJugador->IncreaseHealth();
                    std::cout<<"Vida total: "<<ControladorJugador->getMaxHealth()<<std::endl;
                }
                ControladorJugador->Update(tecla.key.code);
                std::cout << "Tecla pulsada: " << tecla.key.code << std::endl;
            }
            if (tecla.type == sf::Event::KeyReleased){
                ControladorJugador->Frenar(tecla.key.code);
            }
            if(estadoJuego == false) //Estamos en el menu o en la pantalla final
            {
                    estadoJuego = menu->update(tecla);
            }
        }
        if(jugador->getDirection().x == 0.f && jugador->getDirection().y == 0.f){
            ControladorJugador->setPlayer(jugador);
            listaEnemigos = getAllEnemies();
            ControladorJugador->setLista(listaEnemigos);
            ControladorJugador->Attacks();
        }
        //ENEMY MOVE

        

        // TODO: This loops should be inside the gamestate.cpp 
        double delta = clock.getElapsedTime().asMilliseconds() - lastUpdate;


        // DRAW LOOP 
        double tup = delta / UPDATE_INTERVAL; // Parenthesis very important for a proper calculation! DON'T REMOVE
        double percentTick = min(1.0, tup);


        /*////////////////////////////
            
            RENDER LOOP

        ////////////////////////////*/
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
            Hud* hud = Hud::Instance();
            hud->Draw();
        }

        eng->getApp().display();


        /*////////////////////////////
            
            UPDATE LOOP

        ////////////////////////////*/
        if(delta > UPDATE_INTERVAL){
            //std::cout << "GameUpdate() " << std::endl;
            if(estadoJuego == true){ //Estamos jugando! ;-)
                for (Actor *actor : actors) {
                    // CHeck collisions. BAD PERFORMANCE! O(n^2) !!
                    // Can be improved by not checking the pairs that were already checked
                    for (Actor *test : actors) { // TODO: Add bool to stop updating player movement if collided? prevents input event firing between collision event setting dir to 0 and the update event
                        if(actor != test){
                            //std::cout << "------------ CHECKING OVERLAP ------------" << std::endl;
                            bool overlaps = actor->getBoundingBox().intersects( test->getBoundingBox() );
                            if(overlaps){
                                //std::cout << "--------------------------------- OVERLAPS! ----------------------------" << std::endl;
                                test->OnActorOverlap(actor);
                            }
                        }
                    }

                    if(actor->isAsleep() == false) { // Avoid updating actors that should not update right now (ex: out of window bounds,...)
                        actor->Update(delta);
                    }
                }
                //Comprobamos si pasamos de nivel
                Tile* puerta = vMapas[mapaActual]->getPuerta();
                // FloatRect lol = enemyexp->getBoundingBox();
                // FloatRect lol2 = puerta->getBoundingBox();
                // if(lol.intersects(lol2))
                // {
                //     cout << "LOOOOL" << endl;
                // }
                // if(/*getAllEnemies().size() == 0 &&*/ (jugador->getBoundingBox().intersects(puerta->getBoundingBox())) )
                // {
                //     mapaActual++;  
                //     InicializaNivel();
                // }
                if(jugador->getActorLocation().y<100.0)
                {
                    mapaActual++;  
                    InicializaNivel();
                }
            }
            lastUpdate = clock.getElapsedTime().asMilliseconds();

            /*////////////////////////////
            
                DELETE PENDING DELETE ACTORS

            ////////////////////////////*/
            actors.erase(
                std::remove_if(
                    actors.begin(), 
                    actors.end(),
                    [](Actor const * p) { return p->pendingDelete == true; }
                ), 
                actors.end()
            ); 
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
/*/////////////////////////
    \brief Traces a box on the desired location to check for collisions.

    \param rect FLoatRect rectangle for collision check

/////////////////////////*/
Actor* game::boxTraceByObjectType(FloatRect rect, ObjectType type) {
    for (Actor *act : actors) {
        if(act->getObjectType() == type) {
            bool overlaps = act->getBoundingBox().intersects( rect );
            if(overlaps){
                return act;
            }
        }
    }
    return NULL;
}


game::~game() // Destructor
{
 
}
