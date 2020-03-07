#include "src/public/game.h"
#include <iostream>

game::game()
{
    
}
void game::init(/*char* nombre, int AuxMapa*/){
    
    //Creamos una ventana
    //sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
    app.create(sf::VideoMode(largo, alto), "P0. Fundamentos de los Videojuegos. DCCIA");
    app.setFramerateLimit(60); //Esto para la interpolación 
    x = (largo/2);
    y = (alto/2);
    posx = x;
    posy = y;
    futurPosx = posx;
    futurPosy = posy;
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

}
//bucle del juego
void game::run(){
    relojInterpolacion.restart();
    //Bucle del juego
    while (app.isOpen()) {

        //Variables de interpolacion
        AuxInter = relojInterpolacion.getElapsedTime().asMilliseconds();
        relojInterpolacion.restart();
        AuxInter2 += AuxInter;
        AuxInter3 = AuxInter2/AuxInter4;
        aMoverse();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ //TECLA ESC --> CIERRA EL JUEGO
            std::cout<<"Tecla Esc pulsada --> Se sale del juego."<<std::endl;
            app.close(); //cierra el juego
        }
        //Bucle de obtención de eventos
        //sf::Event event;
        /*while (app.pollEvent(tecla)) {

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
        }*/
        //justo aqui arriba se hace el update
        if (AuxInter4<AuxInter2){
            //Entonces se tiene que hacer el update.
            Actualizar();
            AuxInter3 = 0;
            AuxInter2 = 0;
        }
        app.clear();
        //app.draw(sprite);
        Renderizado(AuxInter3, AuxInter);
        app.display();
    }
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
    if(auxMov != true && teclita==sf::Keyboard::Up){
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
        mouve = _derecha;
        //amigo->muevePlayer(_derecha);
    }
    else if(teclita==sf::Keyboard::Left){
        _izquierda=auxMov;
        mouve = _izquierda;
        //amigo->muevePlayer(_izquierda);
    }
}

void game::Renderizado(float interpol, float time){

    //Esto es el famoso render.
    if(interpol < 0 && interpol > 1 && interpol !=1){

        interpol = 1;

    }
    //amigo->moverInterpolado(interpol);
    moverInterpolado(interpol);
    //pinta(time);
    app.draw(sprite);

}
void game::moverInterpolado(float porcentajeInterpolacion){
    if (posx != 0){
        float coorx = posx * (1-porcentajeInterpolacion) + futurPosx * porcentajeInterpolacion;
        float coory = posy * (1-porcentajeInterpolacion) + futurPosy * porcentajeInterpolacion;
        posx=coorx;
        posy=coory;
        sprite.setPosition(posx, posy);
    }
}
void game::pinta(float dTime){
    
}
void game::Actualizar(){

    //el update
    /*if(Mapita->getMapa()==1){
        plantaAbajo();
        //plantaArriba();
    }*/
    if(arriba == true){
        _vertical = -1.0;
        _horizontal = 0.0;
        mover(_horizontal, _vertical); 
    }
    if(abajo == true){
        _vertical = 1.0;
        _horizontal = 0.0;
        mover(_horizontal, _vertical); 
    }
    if (_izquierda == true){
        _vertical = 0.0;
        _horizontal = -1.0;
        mover(_horizontal, _vertical);
    }
    if (_derecha == true){
        _vertical = 0.0;
        _horizontal = 1.0;
        mover(_horizontal, _vertical);
    }
    /*if (tecla.type == sf::Event::KeyPressed){
        //Escape
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
            app.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ //Horizontal
            sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
            //Escala por defecto
            sprite.setScale(1, 1);
            //sprite.move(kVel, 0);
            _vertical = 0.0;
            _horizontal = 1.0;
            mover(_horizontal, _vertical);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ //Horizontal
            sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
            //Reflejo vertical
            sprite.setScale(-1, 1);
            //sprite.move(-kVel, 0);
            _vertical = 0.0;
            _horizontal = -1.0;
            mover(_horizontal, _vertical);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ //Vertical
            sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
            //sprite.move(0, -kVel);
            _vertical = -1.0;
            _horizontal = 0.0;
            mover(_horizontal, _vertical);  
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ //Vertical
            sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
            //sprite.move(0, kVel);
            _vertical = 1.0;
            _horizontal = 0.0;
            mover(_horizontal, _vertical); 
        }
        std::cout << "Tecla pulsada: " << tecla.key.code << std::endl;
    }*/
}
void game::mover(float x, float y){
    posx = futurPosx;
    posy = futurPosy;
    futurPosx=posx+x*velX;
    futurPosy=posy+y*velY;
}

game::~game()
{
    //delete amigo;
    //delete Mapita;
}
