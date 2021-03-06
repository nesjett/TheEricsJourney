#include "../public/Hud.h"
#include "../public/game.h"

Hud* Hud::pInstance = NULL;
Hud* Hud::Instance() {
    if(pInstance == NULL) { 
        pInstance = new Hud;
    } 
    return pInstance;
}
Hud::Hud()
{
    eng = Engine::Instance();
    percent = 1;
    width = 80.0;
    widthEnemigo = width;
    height = 5.f;
    colorHealth100 = sf::Color(0, 204, 102);
    colorHealthLess50 = sf::Color(255, 255, 102);
    colorHealthLess25 = sf::Color(255, 0, 0);
    playerHealth.setPosition(Vector2f(775,eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 50));
    playerHealth.setSize(sf::Vector2f(width, height));
    playerHealth.setFillColor(colorHealth100);
    maxHealth = 0.f;
    currentHealth = 0.f;
    fontHud.loadFromFile("./resources/typos/SupercellMagic.ttf");
    playerHealth.setPosition(Vector2f(775,eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 25));

    //Cargamos los textos de las mejoras
    txtHealth.setFont(fontHud);
    txtMovSpeed.setFont(fontHud);
    txtAttackSpeed.setFont(fontHud);
    txtAttackMore.setFont(fontHud);
    txtMoreDamage.setFont(fontHud);
    txtCritAttack.setFont(fontHud);
    txtHealth.setCharacterSize(20);
    txtMovSpeed.setCharacterSize(20);
    txtAttackSpeed.setCharacterSize(20);
    txtAttackMore.setCharacterSize(20);
    txtMoreDamage.setCharacterSize(20);
    txtCritAttack.setCharacterSize(20);
    txtHealth.setColor(Color::Black);
    txtMovSpeed.setColor(Color::Black);
    txtAttackSpeed.setColor(Color::Black);
    txtAttackMore.setColor(Color::Black);
    txtMoreDamage.setColor(Color::Black);
    txtCritAttack.setColor(Color::Black);
    for(int i = 0; i < 6; i++)
    {
        spritesMejoras.push_back(new Sprite);
    }
    tx1->loadFromFile("./resources/powerups/0.png");
    tx2->loadFromFile("./resources/powerups/1.png");
    tx3->loadFromFile("./resources/powerups/2.png");
    tx4->loadFromFile("./resources/powerups/3.png");
    tx5->loadFromFile("./resources/powerups/4.png");
    tx6->loadFromFile("./resources/powerups/5.png");
    spritesMejoras[0]->setTexture(*tx1);
    spritesMejoras[1]->setTexture(*tx2);
    spritesMejoras[2]->setTexture(*tx3);
    spritesMejoras[3]->setTexture(*tx4);
    spritesMejoras[4]->setTexture(*tx5);
    spritesMejoras[5]->setTexture(*tx6);
    for(int i = 0; i < spritesMejoras.size(); i++)
    {
        spritesMejoras[i]->setOrigin(spritesMejoras[i]->getGlobalBounds().width/2,spritesMejoras[i]->getGlobalBounds().height/2);
    }

    texVentana.loadFromFile("./resources/menu/Windows.png");
    spriteVentana.setTexture(texVentana);
    spriteVentana.setTextureRect(IntRect(1504.f, 960.f, 530.f, 717.f));
    spriteVentana.setScale(0.3f, 0.60f);

    textoMapa.setFont(fontHud);
    textoMapa.setCharacterSize(20);
    textoMapa.setColor(Color::Black);


}
Hud::~Hud()
{
    enemyHealthBars.erase(enemyHealthBars.begin(), enemyHealthBars.end());
}

void Hud::setMaxHealth(float health)
{
    // if(maxHealth > 0.f)
    // {
    //     // float porcentaje = health/maxHealth;
    //     // width = width*porcentaje;
    //     // playerHealth.setSize(Vector2f(width, height));
    // }
    maxHealth = health;
}

void Hud::setCurrentHealth(float health)
{
    setMaxHealth(jugador->getMaxHealth());
    if(health >= 0.f)
    {
        currentHealth = health;
    }
    //Update de las variables que dependen de la vida
    percent = currentHealth / maxHealth;
    playerHealth.setSize(sf::Vector2f(percent*width, height));
    playerHealth.setOrigin(width/2, height/2);
    playerHealth.setFillColor(colorHealth100);
}
void Hud::setNumMapa(int num)
{
    textoMapa.setString("Nivel "+ to_string(num));
}
void Hud::setPlayer(Player* player)
{
    jugador = player;
    setMaxHealth(jugador->getMaxHealth());
    setCurrentHealth(jugador->getCurrentHealth());
}

void Hud::addMejora(PowerUpType tipo)
{
    switch(tipo)
    {
        case health:
            vecesMejora1++;
            break;
        case movementspeed:
            vecesMejora2++;
            break;
        case attackspeed:
            vecesMejora3++;
            break;
        case attackmore:
            vecesMejora4++;
            break;
        case moredamage:
            vecesMejora5++;
            break;
        case critattack:
            vecesMejora6++;
            break;
    }
    txtHealth.setString(to_string(vecesMejora1) + "x");
    txtMovSpeed.setString(to_string(vecesMejora2) + "x");
    txtAttackSpeed.setString(to_string(vecesMejora3) + "x");
    txtAttackMore.setString(to_string(vecesMejora4) + "x");
    txtMoreDamage.setString(to_string(vecesMejora5) + "x");
    txtCritAttack.setString(to_string(vecesMejora6) + "x");
}

void::Hud::resetMejoras()
{
    vecesMejora1 = 0;
    vecesMejora2 = 0;
    vecesMejora3 = 0;
    vecesMejora4 = 0;
    vecesMejora5 = 0;
    vecesMejora6 = 0; 
}
 void Hud::Update()
 {
 }

void Hud::Draw()
{
    //La info de mejoras debe moverse con la camara
    spriteVentana.setPosition(725.f, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 50);
    eng->getApp().draw(spriteVentana);
    textoMapa.setPosition(760.f, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 85);

    eng->getApp().draw(textoMapa);
    setCurrentHealth(jugador->getCurrentHealth());

    //Actualizamos barras de vida de los enemigos
    list<Enemy*> enemigos = game::Instance()->getAllEnemies();
    vector<RectangleShape*>::iterator it;
    for(it=enemyHealthBars.begin(); it != enemyHealthBars.end(); it++)
    {
        delete *it;
    }
    enemyHealthBars.clear();
    int i = 0;
    for (Enemy *enemigo : enemigos) {
        if(enemigo->health_Current >= 0.f)
        {
            percent = enemigo->health_Current / enemigo->health_MAX;
            enemyHealthBars.push_back(new RectangleShape);
            enemyHealthBars[i]->setSize(sf::Vector2f(percent*widthEnemigo, height));
            enemyHealthBars[i]->setFillColor(colorHealthLess25);
            enemyHealthBars[i]->setOrigin(widthEnemigo/2, height/2);
            i++;
        }       
    }

    //Barra de vida del jugador con borde
    playerHealth.setPosition(Vector2f(jugador->getInterpolatedPos().x, jugador->getInterpolatedPos().y - 50));
    for(it=cuadraditos.begin(); it != cuadraditos.end(); it++)
    {
        delete *it;
    }
    cuadraditos.clear();
    int numCuadrados = maxHealth/25.f;//width/20;
    float widthCuadradito = width/numCuadrados; //20;
    eng->getApp().draw(playerHealth);
    for(int i = 0; i < numCuadrados; i++)
    {
        cuadraditos.push_back(new RectangleShape);
        cuadraditos[i]->setSize(sf::Vector2f(widthCuadradito, height));
        cuadraditos[i]->setOrigin(cuadraditos[i]->getGlobalBounds().width/2, cuadraditos[i]->getGlobalBounds().height/2);
        if(i == 0)
        {
            cuadraditos[i]->setPosition(Vector2f(playerHealth.getPosition().x - width/2 + widthCuadradito/2, jugador->getInterpolatedPos().y - 50));
        }
        else{
            cuadraditos[i]->setPosition(Vector2f(cuadraditos[i-1]->getPosition().x + widthCuadradito, jugador->getInterpolatedPos().y - 50));
        }
        cuadraditos[i]->setOutlineColor(sf::Color::Black);
        cuadraditos[i]->setOutlineThickness(1);
        cuadraditos[i]->setFillColor(Color::Transparent);
        eng->getApp().draw(*cuadraditos[i]);
    }

    //Bordes de las barras de los enemigos: se podria hacer en el mismo bucle que actualiza la vida de los enemigos
    RectangleShape borde;
    borde.setSize(sf::Vector2f(widthEnemigo, height));
    borde.setOutlineColor(sf::Color::Black);
    borde.setOutlineThickness(1);
    borde.setFillColor(Color::Transparent);
    borde.setOrigin(widthEnemigo/2, height/2);
    i = 0;
    for (Enemy *enemigo : enemigos) {
        if(enemigo && enemyHealthBars.size() > 0 && enemigo->IsAlive())
        {
            enemyHealthBars[i]->setPosition(enemigo->getInterpolatedPos().x, enemigo->getInterpolatedPos().y - 50);
            borde.setPosition(enemigo->getInterpolatedPos().x, enemigo->getInterpolatedPos().y - 50);
            eng->getApp().draw(borde);
            eng->getApp().draw(*enemyHealthBars[i]);
            i++;       
        }
    }


    //Draw de las mejoras
    int cont = 0;
    if(vecesMejora1 > 0)
    {
        txtHealth.setPosition(Vector2f(755.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 130));
        eng->getApp().draw(txtHealth);
        spritesMejoras[0]->setPosition(Vector2f(805.f, separacion*cont +eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 140));
        eng->getApp().draw(*spritesMejoras[0]);
        cont++;
    }
    if(vecesMejora2 > 0)
    {
        txtMovSpeed.setPosition(Vector2f(755.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 130));
        eng->getApp().draw(txtMovSpeed);
        spritesMejoras[1]->setPosition(Vector2f(810.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 140));
        eng->getApp().draw(*spritesMejoras[1]);
        cont++;
    }
    if(vecesMejora3 > 0)
    {
        txtAttackSpeed.setPosition(Vector2f(755.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 130));
        eng->getApp().draw(txtAttackSpeed);
        spritesMejoras[2]->setPosition(Vector2f(805.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 140));
        eng->getApp().draw(*spritesMejoras[2]);
        cont++;
    }
    if(vecesMejora4 > 0)
    {
        txtAttackMore.setPosition(Vector2f(755.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 130));
        eng->getApp().draw(txtAttackMore);
        spritesMejoras[3]->setPosition(Vector2f(820.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 140));
        eng->getApp().draw(*spritesMejoras[3]);
        cont++;
    }
    if(vecesMejora5 > 0)
    {
        txtMoreDamage.setPosition(Vector2f(755.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 130));
        eng->getApp().draw(txtMoreDamage);
        spritesMejoras[4]->setPosition(Vector2f(820.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 140));
        eng->getApp().draw(*spritesMejoras[4]);
        cont++;
    }
    if(vecesMejora6 > 0)
    {
        txtCritAttack.setPosition(Vector2f(755.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 130));
        eng->getApp().draw(txtCritAttack);
        spritesMejoras[5]->setPosition(Vector2f(820.f,separacion*cont + eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 140));
        eng->getApp().draw(*spritesMejoras[5]);
        cont++;
    }
    //Si no tenemos mejoras mostramos el mensaje: Sin mejoras
    if(vecesMejora1 == 0
    && vecesMejora2 == 0
    && vecesMejora3 == 0
    && vecesMejora4 == 0
    && vecesMejora5 == 0
    && vecesMejora6 == 0)
    {
        Text txtSinMejoras;
        txtSinMejoras.setFont(fontHud);
        txtSinMejoras.setString("Sin mejoras");
        txtSinMejoras.setPosition(745.f, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 190);
        txtSinMejoras.setCharacterSize(15);
        txtSinMejoras.setColor(Color::Black);
        eng->getApp().draw(txtSinMejoras);
    }

}


