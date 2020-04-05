#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <AudioManager.h>
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
    protected:

    private:
        int numItems = 2;

        sf::Font* fuente;
        sf::Text* menuInicial [2];
        sf::Texture* texturaLogo;
        sf::Sprite* logo;
        string itemsMenu [4];
        sf::Color colorItemHover;
        sf::Color colorItemBase;
        int mostrarMenu;
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
        void cambiaColorItems();
        void cargarLogo();

        AudioManager* audioManager;
};
