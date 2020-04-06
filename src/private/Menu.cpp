#include "../public/Menu.h"
#include "../public/Engine.h"


Menu* Menu::menuInstance = 0;


Menu::Menu()
{
    //Prop menu
    mostrarMenu = 0;
    numItems = 2;
    
    //Propiedades de los items del menu
    colorItemHover = sf::Color(197, 36, 36);
    colorItemBase = sf::Color(255, 255, 255);
    separacion = 100;
    actual = 0;

    cargarFuente();
    cargarMenu();
    cambiaColorItems();
    audioManager = AudioManager::getInstance();
    audioManager->menu();
}

Menu::~Menu()
{
    //dtor
}

//Carga de parametros
void Menu::cargarFuente()
{
    fuente = new sf::Font();
    if(!fuente->loadFromFile("./resources/typos/BenguiatBold.ttf"))
    {
        cout << "Error en fuente";
    }

}
void Menu::cambiaColorItems()
{
    for(int i=0;i<numItems;i++){
        if(i == actual){
            menuInicial[actual]->setColor(colorItemHover);
        }else{
            menuInicial[i]->setColor(colorItemBase);
        }
    }
}

void Menu::cargarLogo()
{
    Engine *eng = Engine::Instance();
    texturaLogo = new Texture;
    logo = new Sprite;
    texturaLogo->loadFromFile("./resources/menu/Logo.png");
    logo->setTexture(*texturaLogo);
    logo->setOrigin(logo->getGlobalBounds().width / 2.0, logo->getGlobalBounds().height / 2.0);
    logo->setPosition(eng->getApp().getSize().x / 2.0, eng->getApp().getSize().y / 2.6);
}

void Menu::cargarMenu()
{
    cargarLogo();
    itemsMenu[0] = "Jugar";
    itemsMenu[1] = "Salir";
    itemsMenu[2] = "Item 3";
    itemsMenu[3] = "Item 4";
    Engine *eng = Engine::Instance();
    for(int i = 0; i < numItems; i++)
    {
        menuInicial[i] = new sf::Text();
        menuInicial[i]->setFont(*fuente);
        menuInicial[i]->setString(itemsMenu[i]);
        menuInicial[i]->setOrigin(menuInicial[i]->getGlobalBounds().width / 2.0, menuInicial[i]->getGlobalBounds().height / 2.0);
        //menuInicial[i]->setPosition(eng->getApp().getSize().x / 2.0,  eng->getApp().getSize().y / 1.4 + separacion * i);
        menuInicial[i]->setPosition(eng->getApp().getSize().x / 2.0,  logo->getOrigin().y + (logo->getGlobalBounds().height/2) + separacion * i);
        menuInicial[i]->setColor(colorItemBase);

    }
}


void Menu::draw()
{
    //ventanaMenu->clear();
    Engine *eng = Engine::Instance();
    eng->getApp().draw(*logo);
    for(int i=0;i<numItems;i++)
    {
        eng->getApp().draw(*menuInicial[i]);
    }
    //ventanaMenu->display();
}
   
bool Menu::update(sf::Event tecla)
{
    //No necesitamos delta
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        if(actual == 0)
        {
            audioManager->menu();
            return true;
        }
        else{
            Engine *eng = Engine::Instance();
            eng->getApp().close();
        }
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        if(actual>0)
            actual--;

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        if(actual<(numItems-1))
            actual++;
    }
    cambiaColorItems();
    return false;
}



