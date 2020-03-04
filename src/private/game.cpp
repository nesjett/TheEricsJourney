#include "game.h"
#include <iostream>

game::game()
{

}
void game::init(/*char* nombre, int AuxMapa*/){
    
    //Creamos una ventana
    //sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
    app.create(sf::VideoMode(largo, alto), "P0. Fundamentos de los Videojuegos. DCCIA");

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

    //Bucle del juego
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
                }
                std::cout << "Tecla pulsada: " << tecla.key.code << std::endl;
            }
        }
        app.clear();
        app.draw(sprite);
        app.display();
    }
    /*relojInterpolacion.restart();
    // Start the game loop
    while (app.isOpen())
    {

        AuxInter = relojInterpolacion.getElapsedTime().asMilliseconds();
        relojInterpolacion.restart();
        AuxInter2 += AuxInter;
        AuxInter3 = AuxInter2/AuxInter4;
        // Movimiento
        aMoverse();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ //TECLA ESC --> CIERRA EL JUEGO
            std::cout<<"Tecla Esc pulsada --> Se sale del juego."<<std::endl;
            app.close(); //cierra el juego
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && relojDios->getElapsedTime().asSeconds() > 1.5){ //ACTIVACION MODO DIOS
            if (GodMode == false){
                relojDios->restart();
                GodMode = true;
                std::cout << "Tecla G pulsada --> Modo Dios activado." << std::endl;
            }
            else{
                relojDios->restart();
                GodMode = false;
                std::cout << "Tecla G se ha vuelto a pulsar --> Modo Dios desactivado." << std::endl;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::X) && relojRe->getElapsedTime().asSeconds() > 1.5){
            if(ReMade == false){
                //ReMade = true;
                relojRe->restart();
                std::cout<<"Tecla X pulsada --> Muerte del jugador y reinicio del nivel."<<std::endl;
                if(Mapita->getMapa()==1){
                    init("resources/UltimaPrueba.tmx", 1);
                }
                if(Mapita->getMapa()==2){
                    init("resources/UltimaPrueba2.tmx", 2);
                }
                //init();
                //IMPORTANTEEEEEEEEEE!!!!!! EN ALGUN MOMENTO CUANDO VERIFIQUE QUE REMADE == TRUE PARA MATAR AL JUGADOR HAY QUE PONER
                //REMADE = FALSE.
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::N) && relojNivel->getElapsedTime().asSeconds() > 1.5){
            if(NextLevel == false){
                //NextLevel = true;
                relojNivel->restart();
                std::cout<<"Tecla N pulsada --> Se pasa al siguiente nivel sin necesidad de coger las esferas o acceder a la puerta."<<std::endl;
                if(Mapita->getMapa()==2){
                    init("resources/UltimaPrueba.tmx", 1);
                }
                if(Mapita->getMapa()==1){
                    init("resources/UltimaPrueba2.tmx", 2);
                }
                //IMPORTANTE Lo mismo que con ReMade
            }
        }
        //Ahora se hace el update
        if(AuxInter4<AuxInter2){
            //Hay que hacer el update.
            Actualizar();
            AuxInter3=0;
            AuxInter2=0;
        }
        // Clear screen
        app.clear();
        Mapita->renderMapa(app);
        //Aqui se hace el renderizado
        Renderizado(AuxInter3, AuxInter);
        app.display();
    }*/
}
/*
void game::Renderizado(float interpol, float time){

    //Esto es el famoso render.
    if(interpol < 0 && interpol > 1 && interpol !=1){

        interpol = 1;

    }
    amigo->moverInterpolado(interpol);
    amigo->pinta(app, time);

}
void game::Actualizar(){

    //el update
    if(Mapita->getMapa()==1){
        plantaAbajo();
        //plantaArriba();
    }


    //puedoMover = Mapita->compruebaColision(amigo->dameRectangleShape(), 1);
    //VaX=amigo->getX();
    //VaY=amigo->getY();
    //if(VaX>68 &&VaX<1020&&VaY>30){
      //   amigo->mover(_horizontal, _vertical);
    //}
}
void game::aMoverse(){
    do{
        if (tecla.type == sf::Event::Closed){
            app.close();
        }
        else if(tecla.type==sf::Event::KeyReleased){
            enviar=false;
            auxiliarMov(enviar, tecla.key.code);
        }
        else if(tecla.type==sf::Event::KeyPressed){
            enviar=true;
            auxiliarMov(enviar, tecla.key.code);
        }
    }while(app.pollEvent(tecla));
}
void game::auxiliarMov(bool auxMov, sf::Keyboard::Key teclita){
    if(auxMov!= true&&teclita==sf::Keyboard::Up){
        arriba=auxMov;
    }
    if(auxMov==true&&teclita==sf::Keyboard::Up){
        arriba=auxMov;
    }
    else if(teclita==sf::Keyboard::Down){
        abajo=auxMov;
    }
    else if(teclita==sf::Keyboard::Right){
        _derecha=auxMov;
        amigo->muevePlayer(_derecha);
    }
    else if(teclita==sf::Keyboard::Left){
        _izquierda=auxMov;
        amigo->muevePlayer(_izquierda);
    }
}
void game::plantaAbajo(){
    if(arriba==true){
        _vertical=-1;
        //VaX=
        std::cout<<"la x: "<<amigo->getX()<<std::endl;
        std::cout<<"la y: "<<amigo->getY()<<std::endl;
        if(subir==false){
            amigo->subir();
            subir=true;
        }
        if(cambiado==false){
             if(amigo->getX()>=422&&amigo->getX()<=445&&amigo->getY()>=375&&amigo->getY()<=530){
                amigo->moverY(_vertical);
            }
            if(amigo->getX()>=827&&amigo->getX()<=854&&amigo->getY()>=530){ //segunda escalera, abajo
                amigo->moverY(_vertical);
            }
            if(amigo->getX()>=827&&amigo->getX()<=854&&amigo->getY()<=100){ //Planta de arriba escalera
                amigo->moverY(_vertical);
            }
        }
        else{
            if(amigo->getX()>=490&&amigo->getX()<=513&&amigo->getY()>=375&&amigo->getY()<=530){
                amigo->moverY(_vertical);
            }
            if(amigo->getX()>=895&&amigo->getX()<=922&&amigo->getY()>=530){ //segunda escalera, abajo
                amigo->moverY(_vertical);
            }
            if(amigo->getX()>=895&&amigo->getX()<=922&&amigo->getY()<=100){ //Planta de arriba escalera
                amigo->moverY(_vertical);
            }
        }
    }
    if(abajo!=false){
        _vertical=1;
        if(subir==false){
            amigo->subir();
            subir=true;
        }
        if(cambiado==false){
           if(amigo->getY() >60){
                //amigo->moverY(_vertical);
                if(amigo->getX()>=422&&amigo->getX()<=445&&amigo->getY()>=360&&amigo->getY()<520){ //primera escalera
                    amigo->moverY(_vertical);
                }
                if(amigo->getX()>=827&&amigo->getX()<=854&&amigo->getY()>=529){ //segunda escalera, abajo
                    amigo->moverY(_vertical);
                }
                if(amigo->getX()>=827&&amigo->getX()<=854&&amigo->getY()<=70){ //segunda escalera, arriba
                    amigo->moverY(_vertical);
                }
            }
        }
        else{
            if(amigo->getY() >60){
                //amigo->moverY(_vertical);
                if(amigo->getX()>=490&&amigo->getX()<=513&&amigo->getY()>=360&&amigo->getY()<520){ //primera escalera
                    amigo->moverY(_vertical);
                }
                if(amigo->getX()>=895&&amigo->getX()<=922&&amigo->getY()>=529){ //segunda escalera, abajo
                    amigo->moverY(_vertical);
                }
                if(amigo->getX()>=895&&amigo->getX()<=922&&amigo->getY()<=70){ //segunda escalera, arriba
                    amigo->moverY(_vertical);
                }
            }
        }
    }
    if(_derecha==true){
        _horizontal=1;
        if(amigo->getX()>=52&&amigo->getX()<=945&&amigo->getY()>484&&amigo->getY()<620){ //PLANTA DE ABAJO
            if(subir==true){
                amigo->restaurar();
                subir=false;
            }
            if(cambiado ==false){
                auxPedoX=amigo->getX();
                amigo->setSize(-1.f,1.f);
                amigo->teleporte(auxPedoX+68, amigo->getY());
                cambiado=true;
            }
            amigo->moverX(_horizontal);
            std::cout<<"Ha pulsado la tecla derecha."<<std::endl;
        }
        if(amigo->getX()>=120&&amigo->getX()<=1013&&amigo->getY()<=100){ //barra de arriba
            if(subir==true){
                amigo->restaurar();
                subir=false;
            }
            if(cambiado==false){
                auxPedoX=amigo->getX();
                amigo->setSize(-1.f,1.f);
                amigo->teleporte(auxPedoX+68, amigo->getY());
                cambiado=true;
            }
            amigo->moverX(_horizontal);
            std::cout<<"Ha pulsado la tecla derecha."<<std::endl;
        }
    }
    if(_izquierda==true){
        _horizontal=-1;
        if(amigo->getX()>=62&&amigo->getX()<=953&&amigo->getY()>484&&amigo->getY()<=620){ //PLANTA DE ABAJO
            if(subir==true){
                amigo->restaurar();
                subir=false;
            }
            if(cambiado==true){
                auxPedoX=amigo->getX();
                amigo->setSize(1.f,1.f);
                amigo->teleporte(auxPedoX-68, amigo->getY());
                cambiado=false;
            }
            amigo->moverX(_horizontal);
            std::cout<<"Ha pulsado la tecla izquierda."<<std::endl;
        }
        if(amigo->getX()>=62&&amigo->getX()<=953&&amigo->getY()<=100){ //PLANTA DE ARRIBA
            if(subir==true){
                amigo->restaurar();
                subir=false;
            }
            if(cambiado==true){
                auxPedoX=amigo->getX();
                amigo->setSize(1.f,1.f);
                amigo->teleporte(auxPedoX-68, amigo->getY());
                cambiado=false;
            }
            amigo->moverX(_horizontal);
            std::cout<<"Ha pulsado la tecla izquierda."<<std::endl;
        }
    }
    if(cambiado==false){
        if(amigo->getY()>484&&amigo->getY()<525&&amigo->getX()<377){ //gravedad a la izquierda de la escalera
            amigo->moverY(1);
        }
        if(amigo->getY()>484&&amigo->getY()<525&&amigo->getX()>485){ //gravedad a la derecha de la escalera
            amigo->moverY(1);
        }
        if(amigo->getY()>=80&&amigo->getY()<525&&amigo->getX()>=933){ //arriba derecha
            amigo->moverY(1);
        }
        if(amigo->getY()>=80&&amigo->getY()<525&&amigo->getX()<=72){ //arriba derecha
            amigo->moverY(1);
        }
        if(amigo->getY()>=620){ //teleportar
            //amigo->moverY(_vertical);
            //amigo->setPosicion(amigo->getX(),60);
            amigo->teleporte(amigo->getX(), 80);
        }
        if(amigo->getY()<=-50){
            amigo->teleporte(amigo->getX(), 610);
        }
        if(salto!=false){
        }
        if(amigo->getY()==530&&amigo->getX()>=637&&amigo->getX()<=710){
            //borrar espada
        }
    }
    else{
        if(amigo->getY()>484&&amigo->getY()<525&&amigo->getX()<445){ //gravedad a la izquierda de la escalera
            amigo->moverY(1);
        }
        if(amigo->getY()>484&&amigo->getY()<525&&amigo->getX()>553){ //gravedad a la derecha de la escalera
            amigo->moverY(1);
        }
        if(amigo->getY()>=80&&amigo->getY()<525&&amigo->getX()>=1001){ //arriba derecha
            amigo->moverY(1);
        }
        if(amigo->getY()>=620){ //teleportar
            //amigo->moverY(_vertical);
            //amigo->setPosicion(amigo->getX(),60);
            amigo->teleporte(amigo->getX(), 80);
        }
        if(amigo->getY()<=-50){
            amigo->teleporte(amigo->getX(), 610);
        }
        if(salto!=false){
        }
        if(amigo->getY()==530&&amigo->getX()>=637&&amigo->getX()<=710){
            //borrar espada
        }
    }
}*/

game::~game()
{
    //delete amigo;
    //delete Mapita;
}
