#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <AudioManager.h>
#include <list>
using namespace std;

class Menu
{
    public:
        static Menu *getInstance(){
            if(menuInstance == 0){
                menuInstance = new Menu();
            }
            return menuInstance;
        }
        void render(sf::RenderWindow *gameWindow);
        bool update(sf::Event tecla);
        void draw();
        void cambiarAPantallaFinal(list<float> puntuaciones);
    protected:

    private:
        int numItems = 2;

        sf::Font* fuente;
        sf::Text* menuInicial [2];
        sf::Text* menuFinal [4];
        sf::Texture* texturaLogo;
        sf::Sprite* logo;
        string itemsMenu [4];
        string itemsMenuFinal [4];
        vector<Text*> itemsMnuFinal;
        sf::Color colorItemHover;
        sf::Color colorItemBase;
        bool mostrarMenu;
        int separacion;
        int actual;
        int presionado;
        int idMenu;
        int cont;
        static Menu* menuInstance;
        Menu();
        virtual ~Menu();
        void cargarFuente();
        void cargarMenu();
        void cargarMenuFinal();
        void cambiaColorItems();
        void cargarLogo();
        void cargarLogoFinal();
        list<float> puntos;
        AudioManager* audioManager;

        map<string, vector<Sprite*>> mapItemsMenu;
        void cargarMapaMenu();
        bool updateRaton(Event event);
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
