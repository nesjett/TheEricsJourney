#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <AudioManager.h>
#include <list>
using namespace std;
using namespace sf;
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
        Font* fuente;
        bool MostrarMenuPrincipal;
        Text textoPuntuaciones;

        static Menu* menuInstance;
        Menu();
        virtual ~Menu();
        void cargarFuente();

        float puntos;
        AudioManager* audioManager;

        //Menu inicial a partir de imagenes y control por raton
        map<string, vector<Sprite*>> mapItemsMenu;
        map<string, vector<Sprite*>> mapItemsMenuPuntos;
        void cargarMapaMenu();
        bool updateRaton(Event event, bool* reiniciaJuego);
        string itemSeleccionado;

        Sprite *jugar, *jugarselecc, *salir, *salirselecc;
        Texture texJugar, texJugarselecc, texSalir, texSalirselecc;
        vector<Sprite*> vJugar, vSalir;

        Sprite fondo;
        Texture texFondo;
        Sprite logoLetras;
        Texture texLogoLetras;
        float separacionMenuPPal = 150;
};
