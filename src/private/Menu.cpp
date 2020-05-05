#include "../public/Menu.h"
#include "../public/Engine.h"


Menu* Menu::menuInstance = 0;


Menu::Menu()
{
    //Prop menu
    mostrarMenu = true;
    numItems = 2;
    
    //Propiedades de los items del menu
    colorItemHover = sf::Color(197, 36, 36);
    colorItemBase = sf::Color(255, 255, 255);
    separacion = 100;
    actual = 0;

    cargarFuente();
    cargarMenu();
    cargarMapaMenu();
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
    if(mostrarMenu == false)
    {
        itemsMnuFinal[actual]->setColor(colorItemHover);
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
void Menu::cargarLogoFinal()
{
    Engine *eng = Engine::Instance();
    logo->setScale(0.5,0.5);
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
void Menu::cargarMenuFinal()
{
    Engine *eng = Engine::Instance();
    itemsMnuFinal.push_back(new Text);
    itemsMnuFinal[0]->setFont(*fuente);
    itemsMnuFinal[0]->setString("HAS PERDIDO");
    if(puntos.size() == 3)
    {
        itemsMnuFinal[0]->setString("HAS GANADO");
    }
    itemsMnuFinal[0]->setOrigin(itemsMnuFinal[0]->getGlobalBounds().width / 2.0, itemsMnuFinal[0]->getGlobalBounds().height / 2.0);
    itemsMnuFinal[0]->setPosition(eng->getApp().getSize().x / 2.0,  eng->getApp().getSize().x / 4.0);
    itemsMnuFinal[0]->setColor(colorItemBase);

    for (float puntuacion : puntos) {
        itemsMnuFinal.push_back(new Text);
    }
    vector<Text*>::iterator it;
    int i = 1;
    for(it = itemsMnuFinal.begin()+1; it != itemsMnuFinal.end(); it++)
    {
        (*it)->setFont(*fuente);
        (*it)->setString("Score " + to_string(i) + " : ");
        (*it)->setPosition(eng->getApp().getSize().x / 2.0, itemsMnuFinal[0]->getPosition().y + ((separacion) * i));
        (*it)->setColor(colorItemBase);
        i++;
    }
    i = 1;
    for (float puntuacion : puntos) {
        itemsMnuFinal[i]->setString(itemsMnuFinal[i]->getString() + to_string((int)puntuacion));
        itemsMnuFinal[i]->setOrigin(itemsMnuFinal[i]->getGlobalBounds().width / 2.0, itemsMnuFinal[i]->getGlobalBounds().height / 2.0);
        i++;
    }

    itemsMnuFinal.push_back(new Text);
    itemsMnuFinal[itemsMnuFinal.size()-1]->setFont(*fuente);
    itemsMnuFinal[itemsMnuFinal.size()-1]->setString("Salir");
    itemsMnuFinal[itemsMnuFinal.size()-1]->setOrigin(itemsMnuFinal[itemsMnuFinal.size()-1]->getGlobalBounds().width / 2.0, itemsMnuFinal[itemsMnuFinal.size()-1]->getGlobalBounds().height / 2.0);
    itemsMnuFinal[itemsMnuFinal.size()-1]->setPosition(eng->getApp().getSize().x / 2.0,  itemsMnuFinal[0]->getPosition().y + (separacion*(itemsMnuFinal.size()-1)));
    itemsMnuFinal[itemsMnuFinal.size()-1]->setColor(colorItemBase);
    actual = itemsMnuFinal.size()-1;
    cambiaColorItems();
}
void Menu::cambiarAPantallaFinal(list<float> puntuaciones)
{
    puntos = puntuaciones;
    mostrarMenu = false;
    cargarMenuFinal();
}

void Menu::draw()
{
    Engine *eng = Engine::Instance();
    if(mostrarMenu == true)
    {
        // eng->getApp().draw(*logo);
        // for(int i=0;i<numItems;i++)
        // {
        //     eng->getApp().draw(*menuInicial[i]);
        // }
        eng->getApp().draw(fondo);
        map<string, vector<Sprite*>>::iterator it;

        for ( it = mapItemsMenu.begin(); it != mapItemsMenu.end(); it++)
        {
            if(it->first == itemSeleccionado)
            {
                eng->getApp().draw(*(it->second[1]));
            }else
            {
                eng->getApp().draw(*(it->second[0]));
            }
            

        }
    }
    else{
        vector<Text*>::iterator it;
        for(it = itemsMnuFinal.begin(); it != itemsMnuFinal.end(); it++)
        {
            eng->getApp().draw(*(*it));
        }
    }
}
   
bool Menu::update(sf::Event tecla)
{
    return updateRaton(tecla);
    // //No necesitamos delta
    // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    // {
    //     audioManager->play_menu_ok();
    //     if(actual == 0)
    //     {
    //         audioManager->menu();
    //         return true;
    //     }
    //     else{
    //         Engine *eng = Engine::Instance();
    //         eng->getApp().close();
    //     }
    // }
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    // {
    //     if(mostrarMenu == true)
    //     {
    //         if(actual>0)
    //         {
    //             actual--;
    //             audioManager->play_menu_move();
    //         }
    //     }


    // }
    // else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    // {
    //     if(mostrarMenu == true)
    //     {
    //         if(actual<(numItems-1))
    //         {
    //             actual++;
    //             audioManager->play_menu_move();
    //         }

    //     }
    // }

    // if(mostrarMenu == false)
    //     actual = itemsMnuFinal.size()-1;
    // cambiaColorItems();
    return false;
}



//Nuevos metodos
void Menu::cargarMapaMenu()
{

    jugar = new Sprite();
    jugarselecc = new Sprite();
    salir = new Sprite();
    salirselecc = new Sprite();
    texJugar.loadFromFile("./resources/menu/jugar.png");
    texJugarselecc.loadFromFile("./resources/menu/jugarselecc.png");
    texSalir.loadFromFile("./resources/menu/salir.png");
    texSalirselecc.loadFromFile("./resources/menu/salirselecc.png");
    jugar->setTexture(texJugar);
    jugarselecc->setTexture(texJugarselecc);
    salir->setTexture(texSalir);
    salirselecc->setTexture(texSalirselecc);
    jugar->setOrigin(jugar->getGlobalBounds().width/2,jugar->getGlobalBounds().height/2);
    jugarselecc->setOrigin(jugarselecc->getGlobalBounds().width/2,jugarselecc->getGlobalBounds().height/2);
    salir->setOrigin(salir->getGlobalBounds().width/2,salir->getGlobalBounds().height/2);
    salirselecc->setOrigin(salirselecc->getGlobalBounds().width/2,salirselecc->getGlobalBounds().height/2);
    Engine *eng = Engine::Instance();
    float posX = eng->getApp().getSize().x/2;
    float posY = eng->getApp().getSize().y/2;
    jugar->setPosition(posX, posY + separacion+10);
    jugarselecc->setPosition(posX, posY + separacion+10);
    salir->setPosition(posX, posY + 10 +separacion*2);
    salirselecc->setPosition(posX, posY + 10 + separacion*2);

    vJugar.push_back(jugar);
    vJugar.push_back(jugarselecc);
    vSalir.push_back(salir);
    vSalir.push_back(salirselecc);

    mapItemsMenu.insert({"Jugar",vJugar});
    mapItemsMenu.insert({"Salir",vSalir});

    texFondo.loadFromFile("./resources/menu/main_menu_bg.png");
    fondo.setTexture(texFondo);
    fondo.setPosition(0.f,0.f);
}

bool Menu::updateRaton(Event event)
{
    Engine *eng = Engine::Instance();
    Vector2i pos = sf::Mouse::getPosition(eng->getApp()); // mouse position in window coords
    Vector2f pos2 = eng->getApp().mapPixelToCoords(pos, eng->getApp().getView());

    map<string, vector<Sprite*>>::iterator it;

    string itemSelecAnterior = itemSeleccionado;
    itemSeleccionado = "";
    for ( it = mapItemsMenu.begin(); it != mapItemsMenu.end(); it++)
    {
        if(it->second[0]->getGlobalBounds().contains(pos2))
        {
            itemSeleccionado = it->first;
            if(itemSelecAnterior!=itemSeleccionado)
                audioManager->play_menu_move();
        }
    }

    if(event.type == sf::Event::MouseButtonPressed){
        if(event.mouseButton.button == sf::Mouse::Left){
            if(itemSeleccionado == "Jugar")
            {
                audioManager->play_menu_ok();
                return true;
            }
            if(itemSeleccionado == "Salir")
            {
                audioManager->play_menu_ok();
                Engine *eng = Engine::Instance();
                eng->getApp().close();
            }
        }
    }

    return false;
}