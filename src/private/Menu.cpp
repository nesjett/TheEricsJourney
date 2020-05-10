#include "../public/Menu.h"
#include "../public/Engine.h"


Menu* Menu::menuInstance = 0;


Menu::Menu()
{
    MostrarMenuPrincipal = true;
    cargarFuente();
    cargarMapaMenu();
    audioManager = AudioManager::getInstance();
    audioManager->menu();
}

Menu::~Menu()
{
    //dtor
    delete fuente;
}

//Carga de parametros
void Menu::cargarFuente()
{
    fuente = new sf::Font();
    if(!fuente->loadFromFile("./resources/typos/SupercellMagic.ttf"))
    {
        cout << "Error en fuente";
    }

}
void Menu::MostrarPuntuaciones(float puntuacion, bool victoria)
{
    puntos = puntuacion;
    MostrarMenuPrincipal = false;
    textoPuntuaciones.setFont(*fuente);
    textoPuntuaciones.setString(to_string((int)puntuacion));
    textoPuntuaciones.setCharacterSize(30);
    textoPuntuaciones.setOrigin(textoPuntuaciones.getGlobalBounds().width/2,textoPuntuaciones.getGlobalBounds().height/2);
    textoVictoria.setFont(*fuente);
    textoCartel.setFont(*fuente);
    textoCartel.setString("Puntos");
    textoCartel.setColor(Color::Black);
    textoCartel.setCharacterSize(28);
    if(victoria)
    {
        textoVictoria.setString("VICTORIA");
    }
    else{
        textoVictoria.setString("DERROTA");
    }
    textoVictoria.setCharacterSize(100);
    textoVictoria.setOrigin(textoVictoria.getGlobalBounds().width/2,textoVictoria.getGlobalBounds().height/2);
    textoCartel.setOrigin(textoCartel.getGlobalBounds().width/2,textoCartel.getGlobalBounds().height/2);

    audioManager->menu();
}

void Menu::draw()
{
    Engine *eng = Engine::Instance();
    if(MostrarMenuPrincipal == true)
    {
        eng->getApp().draw(fondo);
        eng->getApp().draw(logoLetras);
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
        eng->getApp().draw(fondo2);
        textoVictoria.setPosition(eng->getApp().getSize().x/2,eng->getApp().getSize().y/2 - 200);
        textoCartel.setPosition(eng->getApp().getSize().x/2,eng->getApp().getSize().y/2 - 75);
        textoPuntuaciones.setPosition(eng->getApp().getSize().x/2,eng->getApp().getSize().y/2 + 20);
        eng->getApp().draw(textoVictoria);
        eng->getApp().draw(textoCartel);
        eng->getApp().draw(textoPuntuaciones);
        map<string, vector<Sprite*>>::iterator it;

        for ( it = mapItemsMenuPuntos.begin(); it != mapItemsMenuPuntos.end(); it++)
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
}
   
bool Menu::update(sf::Event event, bool *reiniciaJuego)
{
    Engine *eng = Engine::Instance();
    Vector2i pos = sf::Mouse::getPosition(eng->getApp()); // mouse position in window coords
    Vector2f pos2 = eng->getApp().mapPixelToCoords(pos, eng->getApp().getView());

    map<string, vector<Sprite*>>::iterator it;

    string itemSelecAnterior = itemSeleccionado;
    itemSeleccionado = "";
    if(MostrarMenuPrincipal)
    {
        for ( it = mapItemsMenu.begin(); it != mapItemsMenu.end(); it++)
        {
            if(it->second[0]->getGlobalBounds().contains(pos2))
            {
                itemSeleccionado = it->first;
                if(itemSelecAnterior!=itemSeleccionado)
                    audioManager->play_menu_move();
            }
        }
    }else{
        for ( it = mapItemsMenuPuntos.begin(); it != mapItemsMenuPuntos.end(); it++)
        {
            if(it->second[0]->getGlobalBounds().contains(pos2))
            {
                itemSeleccionado = it->first;
                if(itemSelecAnterior!=itemSeleccionado)
                    audioManager->play_menu_move();
            }
        }
    }


    if(event.type == sf::Event::MouseButtonPressed){
        if(event.mouseButton.button == sf::Mouse::Left){
            if(itemSeleccionado == "Jugar")
            {
                audioManager->play_menu_ok();
                audioManager->menu();
                return true;
            }
            if(itemSeleccionado == "Salir")
            {
                audioManager->play_menu_ok();
                Engine *eng = Engine::Instance();
                eng->getApp().close();
            }
            if(itemSeleccionado == "Reinicia")
            {
                *reiniciaJuego = true;
                audioManager->play_menu_ok();
                audioManager->menu();
                return true;
            }
        }
    }

    return false;
}



//Nuevos metodos
void Menu::cargarMapaMenu()
{

    jugar = new Sprite();
    jugarselecc = new Sprite();
    salir = new Sprite();
    salirselecc = new Sprite();
    reintentar = new Sprite();
    reintentarselecc = new Sprite();
    texJugar.loadFromFile("./resources/menu/jugar.png");
    texJugarselecc.loadFromFile("./resources/menu/jugarselecc.png");
    texSalir.loadFromFile("./resources/menu/salir.png");
    texSalirselecc.loadFromFile("./resources/menu/salirselecc.png");
    texreintenar.loadFromFile("./resources/menu/reintentar.png");
    texreintentarselecc.loadFromFile("./resources/menu/reintentarselecc.png");
    jugar->setTexture(texJugar);
    jugarselecc->setTexture(texJugarselecc);
    salir->setTexture(texSalir);
    salirselecc->setTexture(texSalirselecc);
    reintentar->setTexture(texreintenar);
    reintentarselecc->setTexture(texreintentarselecc);
    jugar->setOrigin(jugar->getGlobalBounds().width/2,jugar->getGlobalBounds().height/2);
    jugarselecc->setOrigin(jugarselecc->getGlobalBounds().width/2,jugarselecc->getGlobalBounds().height/2);
    salir->setOrigin(salir->getGlobalBounds().width/2,salir->getGlobalBounds().height/2);
    salirselecc->setOrigin(salirselecc->getGlobalBounds().width/2,salirselecc->getGlobalBounds().height/2);
    reintentar->setOrigin(reintentar->getGlobalBounds().width/2,reintentar->getGlobalBounds().height/2);
    reintentarselecc->setOrigin(reintentarselecc->getGlobalBounds().width/2,reintentarselecc->getGlobalBounds().height/2);
    Engine *eng = Engine::Instance();
    float posX = eng->getApp().getSize().x/2;
    float posY = eng->getApp().getSize().y/2;
    jugar->setPosition(posX, posY + separacionMenuPPal);
    jugarselecc->setPosition(posX, posY + separacionMenuPPal);
    salir->setPosition(posX, posY + separacionMenuPPal + separacionMenuPPal/2);
    salirselecc->setPosition(posX, posY + + separacionMenuPPal +separacionMenuPPal/2);
    reintentar->setPosition(posX, posY + separacionMenuPPal);
    reintentarselecc->setPosition(posX, posY + separacionMenuPPal);

    vJugar.push_back(jugar);
    vJugar.push_back(jugarselecc);
    vSalir.push_back(salir);
    vSalir.push_back(salirselecc);
    vReintentar.push_back(reintentar);
    vReintentar.push_back(reintentarselecc);

    mapItemsMenu.insert({"Jugar",vJugar});
    mapItemsMenu.insert({"Salir",vSalir});

    mapItemsMenuPuntos.insert({"Reinicia",vReintentar});
    mapItemsMenuPuntos.insert({"Salir",vSalir});

    texFondo.loadFromFile("./resources/menu/pantallamenu.png");
    fondo.setTexture(texFondo);
    fondo.setPosition(0.f,0.f);
    texFondo2.loadFromFile("./resources/menu/pantallapuntos.png");
    fondo2.setTexture(texFondo2);
    fondo2.setPosition(0.f,0.f);
    texLogoLetras.loadFromFile("./resources/menu/logoletras2.png");
    logoLetras.setTexture(texLogoLetras);
    logoLetras.setScale(0.5,0.5);
    logoLetras.setOrigin(salirselecc->getGlobalBounds().width/2,salirselecc->getGlobalBounds().height/2);
    logoLetras.setPosition(posX-10.f, 30.f);

}

