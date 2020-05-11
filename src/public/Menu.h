#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <AudioManager.h>
#include <list>
using namespace std;
using namespace sf;

/**
 * Utilizaremos Menu para mostrar tanto el menu principal como la pantalla de puntuaciones. Es un singleton.
 */
class Menu
{
    public:
        static Menu *getInstance(){
            if(menuInstance == 0){
                menuInstance = new Menu();
            }
            return menuInstance;
        }
        bool update(sf::Event event, bool* reiniciaJuego);
        void draw();
        void MostrarPuntuaciones(float puntuacion, bool victoria);
    protected:

    private:
        static Menu* menuInstance;
        AudioManager* audioManager;
        Menu();
        virtual ~Menu();

        //Fuente del texto, para escribir la puntuacion
        Font* fuente;
        bool MostrarMenuPrincipal; //Para saber si mostrar menu inicial o de puntuaciones
        Text textoPuntuaciones, textoCartel, textoVictoria; 
        float puntos;
        void cargarFuente();


        //Menu inicial a partir de imagenes y control por raton
        //Hacer que los items del menu sean imagenes nos permitiria personalizarlo mas
        map<string, vector<Sprite*>> mapItemsMenu;
        map<string, vector<Sprite*>> mapItemsMenuPuntos;
        void cargarElementosMenu();
        string itemSeleccionado;

        Sprite *jugar, *jugarselecc, *salir, *salirselecc, *reintentar, *reintentarselecc;
        Texture texJugar, texJugarselecc, texSalir, texSalirselecc, texreintenar, texreintentarselecc;
        vector<Sprite*> vJugar, vSalir, vReintentar;

        Sprite fondo; //Fondo de menu principal
        Sprite fondo2; //Fondo de puntuaciones
        Texture texFondo;
        Texture texFondo2;
        Sprite logoLetras; //Logo del juego
        Texture texLogoLetras;
        float separacionMenuPPal = 160; //Separacion entre elementos del menu
};
