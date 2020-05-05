#include "../public/game.h"

#include "../public/traps/Spikes.h"
#include "../public/traps/Saw.h"
#include "../public/particles/PlayerHit.h"
#include "../public/particles/Fireball_Explosion.h"

#define UPDATE_INTERVAL (1000/35.0)

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
    Hud* hud = Hud::Instance();
    hud->setPlayer(jugador);
    InicializaNivel();
}

void game::InicializaNivel()
{
    //Limpiamos los datos de los colisionables del mapa anterior
    for (Actor *actor : actors) { 
        if(actor->getObjectType() == worldstatic || actor->getObjectType() == door || actor->getObjectType() == worlddynamic)
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
        string nombreMapa = "MapaN"+to_string(mapaActual+1)+".tmx";
        vMapas.push_back(new Mapa(nombreMapa));

        //Cargamos las colisiones del nivel
        list<Actor*> mapColisionables = vMapas[mapaActual]->getActors();
        for (Actor *tile : mapColisionables)
        {
            actors.push_back(tile);
        }
        //Protagonista set location al inicio del mapa
        jugador->setActorLocation(Vector2f(350.0,850.0));
        
        //Set vista a la primera parte del mapa
        //eng->ChangeAppView(0);

        //Epmpezamos a correr el tiempo del nivel
        lastUpdateLevelClock = levelClock.getElapsedTime().asSeconds();
    }
    else{
        //Cargamos la pantalla de puntuaciones
        EndGame();
    }
}






//bucle del juego
void game::run(){

    /***********************************
     * TEST Actors, pawns and projectiles
     ***********************************/
    actors.push_back(jugador);
    jugador->setActorLocation(Vector2f(350.0,850.0));
    
    listaEnemigos = getAllEnemies();
    ControladorJugador = new PlayerController(jugador, listaEnemigos);

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
            }
            ControladorJugador->Update(tecla);
            ControladorJugador->Mover(tecla);
            if (tecla.type == sf::Event::MouseButtonReleased){
                ControladorJugador->Frenar();
            }
            /*if (tecla.type == sf::Event::KeyReleased){
                ControladorJugador->Frenar(tecla.key.code);
            }*/
            if(estadoJuego == false) //Estamos en el menu o en la pantalla final
            {
                    estadoJuego = menu->update(tecla);
            }
        }
        listaEnemigos = getAllEnemies();
        ControladorJugador->setAttack(listaEnemigos);
        //ENEMY MOVE

        

        // TODO: This loops should be inside the gamestate.cpp 
        double delta = clock.getElapsedTime().asMilliseconds() - lastUpdate;


        // DRAW LOOP 
        double tup = delta / UPDATE_INTERVAL; // Parenthesis very important for a proper calculation! DON'T REMOVE
        double percentTick = min(1.0, tup);


        /*////////////////////////////
            
            RENDER LOOP

        ////////////////////////////*/
        eng->getApp().clear(sf::Color(200,193,219,255)); 
        
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


        // Draw particles, should do in another thread..?
        for (auto&& Emitter: Particles) { 
            if(Emitter) {
                if(Emitter->IsPendingDelete()) { // Delete emitters that in last game loop where marked to delete.
                    Emitter.reset();
                    continue;
                }
            } else {
                continue;
            }
            
            Emitter->Draw(delta);
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
                CondicionVictoria();
                Hud* hud = Hud::Instance();
                hud->Update();
            }
            lastUpdate = clock.getElapsedTime().asMilliseconds();

            /*////////////////////////////
            
                DELETE PENDING DELETE ACTORS

            ////////////////////////////*/
            // DELETE Pending delete actors
            // TODO: COuld be done one by one in the above loop so we dont make two loops for almost the same thin

            for (Actor *actor : actors) {
                if(actor->pendingDelete == true) { 
                    actorsPendingDelete.push_back(actor);
                }
            }
            actors.erase(
                std::remove_if(
                    actors.begin(), 
                    actors.end(),
                    [](Actor const * p) { return p->pendingDelete == true; }
                ), 
                actors.end()
            );
            for (Actor *actor : actorsPendingDelete) {
                if(dynamic_cast<Enemy*>(actor)) {
                    //EnemyDied(); // If we are deleting an enemy, try to spawn another
                }
                //if(!dynamic_cast<Mejora*>(actor))
                    delete actor;
            }
            actorsPendingDelete.clear();
        }
        

    }
}

list<Enemy*> game::getAllEnemies(){
    list<Enemy*> tmp;
    Enemy* tmpE = NULL;
    for (Actor *actor : actors) {
        if ( dynamic_cast<Enemy*>( actor ) ) {
            tmpE = dynamic_cast<Enemy*>(actor);
            tmp.push_back(tmpE);
        }
    }
    return tmp;
}

list<Projectile*> game::getAllProjectiles(){
    list<Projectile*> tmp;
    Projectile* tmpE = NULL;
    for (Actor *actor : actors) {
        if ( dynamic_cast<Projectile*>( actor ) ) {
            tmpE = dynamic_cast<Projectile*>(actor);
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

PlayerController* game::getPlayerController(){
    return ControladorJugador;
}

list<Mejora*> game::getMejoras(){
    list<Mejora*> tmp;
    Mejora* tmpE = NULL;
    for (Actor *actor : actors) {
        if ( dynamic_cast<Mejora*>( actor ) ) {
            tmpE = dynamic_cast<Mejora*>(actor);
            tmp.push_back(tmpE);
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

void game::CondicionVictoria()
{
    //Pasar al siguiente nivel: el jugador pasa por la puerta y no hay enemigos vivos
    if(getAllEnemies().size() == 0)
    {
        for(Mejora* mejora : getMejoras())
        {
            if(!mejora->utilizada)
                mejora->activada = true;
        }
        for(Actor* actor : actors)
        {
            if(dynamic_cast<Door*>(actor) && dynamic_cast<Door*>(actor)->superior == true && dynamic_cast<Door*>(actor)->abierta == false)
                dynamic_cast<Door*>(actor)->openDoor();
                // dynamic_cast<Door*>(actor)->
        }
        if(jugador->getActorLocation().y < 100.0)
        {
            mapaActual++;  
            InicializaNivel();
        }
    }
    //Acabar partida porque has muerto
    if(!jugador->IsAlive())
    {
        //Calculamos las puntuaciones por nivel
        float porcentaje = (1 - (levelClock.getElapsedTime().asSeconds()-lastUpdateLevelClock)/600); //1 - minutos_transcrridos/100
        float points = porcentaje*1000000; //Puntuacion max es de 1.000.000
        pointsPerLevel.push_back(points);

        EndGame();
    }
}

//Terminar el juego
void game::EndGame()
{
    //Cambiamos a pantalla final
    estadoJuego = false;
    menu->cambiarAPantallaFinal(pointsPerLevel);
    Engine* eng = Engine::Instance();
    eng->setView(0.f, 0.f);

    //Eliminamos los enemigos, si es el caso es que el jugador ha muerto

}


void game::SpawnEmitterAtLocation(int Effect, Vector2f Location, Vector2f Rot) {
    switch (Effect)
    {
    case 0: // Hit effect
        //unique_ptr<Cascade> t = make_unique<Cascade>(Location);
        Particles.push_back(make_unique<PlayerHit>(Location));
        break;
    case 1: // Explosion
        //unique_ptr<Cascade> t = make_unique<Cascade>(Location);
        Particles.push_back(make_unique<Fireball_Explosion>(Location));
        break;
    
    default:
        break;
    }
}

game::~game() // Destructor
{
 
}
