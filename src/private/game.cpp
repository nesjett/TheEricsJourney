#include "../public/game.h"

#include "../public/traps/Spikes.h"
#include "../public/traps/Saw.h"
#include "../public/particles/PlayerHit.h"
#include "../public/particles/Fireball_Explosion.h"
#include "../public/particles/EfectoMejora.h"
#include "../public/particles/Astillas.h"
#include "../public/particles/Coin.h"
#include "../public/enemies/BouncingBoss.h"
#include "../public/particles/Rockexplosion.h"

#define UPDATE_INTERVAL (1000/25.0)

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
void game::init(){
    //Creamos la ventana del juego
    eng = Engine::Instance();
    eng->CreateApp(sf::VideoMode(largo, alto), "The Eric's Journey");


    estadoJuego = false;
    menu = Menu::getInstance();
    mapaActual = 0;
    PlayerPoints = 0;
    MapasTotales = 12;
}
void game::RestartGame()
{
    delete ControladorJugador;
    mapaActual = 0;
    PlayerPoints = 0;
    jugador = new Player();
    Hud* hud = Hud::Instance();
    hud->setPlayer(jugador);
    InicializaNivel();
    ControladorJugador = new PlayerController(jugador); // TODO: Should use unique_ptr?
}
void game::StartGame()
{
    mapaActual = 0;
    PlayerPoints = 0;
    jugador = new Player();
    Hud* hud = Hud::Instance();
    hud->setPlayer(jugador);
    InicializaNivel();
    //actors.push_back(jugador);
    ControladorJugador = new PlayerController(jugador);
}
void game::InicializaNivel()
{
    //Limpiamos los datos de los colisionables del mapa anterior
    for (Actor *actor : actors) { 
        if(actor->getObjectType() == worldstatic || actor->getObjectType() == door || actor->getObjectType() == worlddynamic || actor->getObjectType() == powerup)
            actor->setLifespan(0.0);
    }

    //Guardamos la puntuacion del nivel anterior
    if(estadoJuego == true) //Nos aseguramos de que lastUpdateLevelClock este inicializado
    {
        float porcentaje = (1 - (levelClock.getElapsedTime().asSeconds()-lastUpdateLevelClock)/6000); //1 - minutos_transcrridos/1000
        PlayerPoints = PlayerPoints + porcentaje*2000; 
    }


    if(mapaActual < NumMaxNiveles) 
    {
        //Cargamos el nivel, borrando el anterior
        if(mapa)
            delete mapa;
        string nombreMapa = "Mapa"+to_string(mapaActual+1)+".tmx";
        mapa  = new Mapa(nombreMapa);
        Hud* hud = Hud::Instance();
        hud->setNumMapa(mapaActual+1);

        //Cargamos las colisiones del nivel
        list<Actor*> mapActors = mapa->getActors();
        for (Actor *mapActor : mapActors)
        {
            actors.push_back(mapActor);
        }
        //Queremos que el jugador se dibuje el ultimo, para que este por encima de todo
        actors.remove(jugador);
        actors.push_back(jugador);

        //Protagonista set location al inicio del mapa
        jugador->setActorLocation(Vector2f(350.0,850.0));

        //Epmpezamos a correr el tiempo del nivel
        lastUpdateLevelClock = levelClock.getElapsedTime().asSeconds();
    }
    else{
        //Cargamos la pantalla de puntuaciones porque no hay mas niveles
        EndGame();
    }
}






//bucle del juego
void game::run(){ 
    
    /***********************************
     * Game loop
     ***********************************/
    sf::Clock clock;
    sf::Int64 lastUpdate = clock.getElapsedTime().asMilliseconds();

    while (eng->getApp().isOpen()) {
        //game Loop.
        while (eng->getApp().pollEvent(tecla)) { //Loop that handles key events (mouse and keyboard) 
                
            if (tecla.type == sf::Event::Closed){
                eng->getApp().close();
            }
            if (tecla.type == sf::Event::KeyPressed){ //Handling special keys
                //Escape to close the game
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    eng->getApp().close();
                } 
                //Tab to kill all the enemies and go to the next level.
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)){
                    KillAllEnemies();
                }
            }
            if(ControladorJugador) //PlayerController manages all the events and methods of the player.
            {
                ControladorJugador->Update(tecla); /*Key Event is passed as parameter to the
                PlayerController in order to manage the Player with the user's commands.*/
            }
            if(estadoJuego == false) //Estamos en el menu o en la pantalla final
            {
                bool reiniciaJuego = false;
                estadoJuego = menu->update(tecla, &reiniciaJuego);
                if(estadoJuego == true && reiniciaJuego == false)
                {
                    StartGame();
                }
                if(reiniciaJuego == true)
                {
                    RestartGame();
                }
            }
        }


        

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
            mapa->render();
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
            if(estadoJuego == true){ //Estamos jugando! ;-)
                for (Actor *actor : actors) {
                    // CHeck collisions. BAD PERFORMANCE! O(n^2) !!
                    // Can be improved by not checking the pairs that were already checked
                    //TODO: should do in another thread
                    for (Actor *test : actors) { // TODO: Add bool to stop updating player movement if collided? prevents input event firing between collision event setting dir to 0 and the update event
                        if(actor != test){
                            bool overlaps = actor->getBoundingBox().intersects( test->getBoundingBox() );
                            if(overlaps){
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
                    if(getPlayerCharacter()->GetTarget() && getPlayerCharacter()->GetTarget() == actor){
                        getPlayerCharacter()->ClearTarget();
                    }
                }
                delete actor;
            }
            actorsPendingDelete.clear();
        }
        

    }
}

void game::KillAllEnemies() {
    for (Actor *actor : actors) {
        if ( dynamic_cast<Enemy*>( actor ) ) {
            actor->setLifespan(0.f);
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
void game::Almacenaenemy(Actor* proj){
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

/* 
* @param IgnoreDir ignore actors that have the same dir as the ignored actors. 0 to compare X axis, 1 to compare Y axis, 2 to not compare axis location
*/
Actor* game::boxTraceByObjectType(FloatRect rect, ObjectType type, list<Actor*> ActorsToIgnore, int IgnoreDir = 0) {
    for (Actor *act : actors) {
        if(ActorsToIgnore.size() > 0) {
            for (Actor *ignore : ActorsToIgnore) {
                if(act != ignore)  { // filter if the actor is in the ignore list
                    switch (IgnoreDir)
                    {
                    case 0:
                        if((act->getActorLocation().x != ignore->getActorLocation().x)){
                            if(act->getObjectType() == type) {
                                bool overlaps = act->getBoundingBox().intersects( rect );
                                if(overlaps){
                                    return act;
                                }
                            }
                        }
                        break;

                    case 1:
                        if((act->getActorLocation().y != ignore->getActorLocation().y)){
                            if(act->getObjectType() == type) {
                                bool overlaps = act->getBoundingBox().intersects( rect );
                                if(overlaps){
                                    return act;
                                }
                            }
                        }
                        break;
                    
                    default:
                        if(act->getObjectType() == type) {
                            bool overlaps = act->getBoundingBox().intersects( rect );
                            if(overlaps){
                                return act;
                            }
                        }
                        break;
                    }
                    
                }
            }
        } else {
            
            if(act->getObjectType() == type) {
                bool overlaps = act->getBoundingBox().intersects( rect );
                if(overlaps){
                    return act;
                }
            }
            
        }
    }
    return NULL;
}

void game::CondicionVictoria()
{
    //Acabar partida porque has muerto
    if(!jugador->IsAlive())
    {
        float porcentaje = (1 - (levelClock.getElapsedTime().asSeconds()-lastUpdateLevelClock)/6000); //1 - minutos_transcrridos/1000
        PlayerPoints = PlayerPoints + porcentaje*2000; //Puntuacion max es de 2000

        EndGame();
        return;
    }
    //Pasar al siguiente nivel: el jugador pasa por la puerta y no hay enemigos vivos
    if(getAllEnemies().size() == 0)
    {
        for(Mejora* mejora : getMejoras())
        {
            if(!mejora->utilizada)
                mejora->activada = true;
        }

        if(getMejoras().size() > 0) {
            return;
        }

        Door* puerta;
        for(Actor* actor : actors)
        {
            if(dynamic_cast<Door*>(actor) && dynamic_cast<Door*>(actor)->superior == true && dynamic_cast<Door*>(actor)->abierta == false)
            {
                dynamic_cast<Door*>(actor)->openDoor();
            }
            if(dynamic_cast<Tile*>(actor) && dynamic_cast<Tile*>(actor)->esPuerta == true)
            {
                dynamic_cast<Tile*>(actor)->setLifespan(0.f);
            }
        }
        if(jugador->getActorLocation().y < 100.f) //Se comprueba si el jugador ha pasado por la puerta
        {
            mapaActual++;  
            InicializaNivel();
        }
    }
}

//Terminar el juego
void game::EndGame()
{
    //Cambiamos a pantalla final
    estadoJuego = false;
    if(jugador->IsAlive())
    {
        menu->MostrarPuntuaciones(PlayerPoints, true);
    }else
    {
        menu->MostrarPuntuaciones(PlayerPoints, false);
    }
    Engine* eng = Engine::Instance();
    eng->resetView();

    //Reseteamos la HUD
    Hud::Instance()->resetMejoras();
    //Eliminamos todos los actores
    for(Actor* actor : actors)
    {
        actor->setLifespan(0.f);
    }

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
    case 2: // Mejora
        Particles.push_back(make_unique<EfectoMejora>(Location));
        break;
    case 3: // destruye flecha
        Particles.push_back(make_unique<Astillas>(Location));
        break;
    case 4: // destruye roca
        Particles.push_back(make_unique<Rockexplosion>(Location));
        break;

    case 10: // Puntos
        Particles.push_back(make_unique<Coin>(Location));
        break;
    default:
        break;
    }
}

game::~game() // Destructor
{
 
}
