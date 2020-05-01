#include "../public/Hud.h"
#include "../public/game.h"

Hud* Hud::pInstance = NULL;
Hud* Hud::Instance() {
    if(pInstance == NULL) { // If not created earlier, create a new instance and return it
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
    playerHealth.setPosition(Vector2f(875,eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 50));
    playerHealth.setSize(sf::Vector2f(width, height));
    playerHealth.setFillColor(colorHealth100);
    maxHealth = 0.f;
    currentHealth = 0.f;
    fontHud.loadFromFile("./resources/typos/BenguiatBold.ttf");
    playerHealth.setPosition(Vector2f(875,eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 25));

    //Cargamos los textos de las mejoras
    txtHealth.setFont(fontHud);
    txtMovSpeed.setFont(fontHud);
    txtAttackSpeed.setFont(fontHud);
    txtAttackMore.setFont(fontHud);
    txtHealth.setCharacterSize(20);
    txtMovSpeed.setCharacterSize(20);
    txtAttackSpeed.setCharacterSize(20);
    txtAttackMore.setCharacterSize(20);
    for(int i = 0; i < 4; i++)
    {
        spritesMejoras.push_back(new Sprite);
    }
    Texture *tx1 = new Texture();
    Texture *tx2 = new Texture();
    Texture *tx3 = new Texture();
    Texture *tx4 = new Texture();
    tx1->loadFromFile("./resources/powerups/0.png");
    tx2->loadFromFile("./resources/powerups/1.png");
    tx3->loadFromFile("./resources/powerups/2.png");
    tx4->loadFromFile("./resources/powerups/3.png");
    spritesMejoras[0]->setTexture(*tx1);
    spritesMejoras[1]->setTexture(*tx2);
    spritesMejoras[2]->setTexture(*tx3);
    spritesMejoras[3]->setTexture(*tx4);
    for(int i = 0; i < 4; i++)
    {
        spritesMejoras[i]->setOrigin(spritesMejoras[i]->getGlobalBounds().width/2,spritesMejoras[i]->getGlobalBounds().height/2);
    }


}
Hud::~Hud()
{
    enemyHealthBars.erase(enemyHealthBars.begin(), enemyHealthBars.end());
}

void Hud::setMaxHealth(float health)
{
    if(maxHealth > 0.f)
    {
        float porcentaje = health/maxHealth;
        width = width*porcentaje;
        playerHealth.setSize(Vector2f(width, height));
    }
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
    // if(percent <= 0.5f && percent > 0.25f)
    // {
    //     playerHealth.setFillColor(colorHealthLess50);
    // }
    // if(percent <= 0.25f)
    // {
    //     playerHealth.setFillColor(colorHealthLess25);
    // }
}

void Hud::setPlayer(Player* player)
{
    jugador = player;
    setMaxHealth(jugador->getMaxHealth());
    setCurrentHealth(jugador->getCurrentHealth());
}

void Hud::addMejora(Mejora mejora)
{
    // Mejora* mjo = new Mejora(mejora);
    // vMejoras.push_back(mjo);
    switch(mejora.tipoMejora)
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
    }
    txtHealth.setString(to_string(vecesMejora1) + "x");
    txtMovSpeed.setString(to_string(vecesMejora2) + "x");
    txtAttackSpeed.setString(to_string(vecesMejora3) + "x");
    txtAttackMore.setString(to_string(vecesMejora4) + "x");
}
 void Hud::Update()
 {
    setCurrentHealth(jugador->getCurrentHealth());
    list<Enemy*> enemigos = game::Instance()->getAllEnemies();
    enemyHealthBars.erase(enemyHealthBars.begin(), enemyHealthBars.end());
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
            // if(percent <= 0.5f && percent > 0.25f)
            // {
            //     enemyHealthBars[i]->setFillColor(colorHealthLess50);
            // }
            // if(percent <= 0.25f)
            // {
            //     enemyHealthBars[i]->setFillColor(colorHealthLess25);
            // }
            i++;
        }       
    }
 }

void Hud::Draw()
{
    //Barra de vida del jugador con borde
    playerHealth.setPosition(Vector2f(jugador->getInterpolatedPos().x, jugador->getInterpolatedPos().y - 50));
    //cuadraditos.erase(cuadraditos.begin(),cuadraditos.end());
    cuadraditos.clear();
    int numCuadrados = width/20;
    eng->getApp().draw(playerHealth);
    for(int i = 0; i < numCuadrados; i++)
    {
        cuadraditos.push_back(new RectangleShape);
        cuadraditos[i]->setSize(sf::Vector2f(20, height));
        cuadraditos[i]->setOrigin(cuadraditos[i]->getGlobalBounds().width/2, cuadraditos[i]->getGlobalBounds().height/2);
        if(i == 0)
        {
            cuadraditos[i]->setPosition(Vector2f(playerHealth.getPosition().x - width/2 + 10, jugador->getInterpolatedPos().y - 50));
        }
        else{
            cuadraditos[i]->setPosition(Vector2f(cuadraditos[i-1]->getPosition().x + 20, jugador->getInterpolatedPos().y - 50));
        }
        cuadraditos[i]->setOutlineColor(sf::Color::Black);
        cuadraditos[i]->setOutlineThickness(1);
        cuadraditos[i]->setFillColor(Color::Transparent);
        eng->getApp().draw(*cuadraditos[i]);
    }

    //Barras de vida de los enemigos con borde
    // for(int i = 0; i < enemigos.size(); i++)
    // {
    //     enemyHealthBars[i].setPosition(enemigos[i]->getInterpolatedPos().x, enemigos[i]->getInterpolatedPos().y - 50);
    //     borde.setPosition(enemigos[i]->getInterpolatedPos().x, enemigos[i]->getInterpolatedPos().y - 50);
    //     eng->getApp().draw(borde);
    //     eng->getApp().draw(enemyHealthBars[i]);
    // }
    RectangleShape borde;
    borde.setSize(sf::Vector2f(widthEnemigo, height));
    borde.setOutlineColor(sf::Color::Black);
    borde.setOutlineThickness(1);
    borde.setFillColor(Color::Transparent);
    borde.setOrigin(widthEnemigo/2, height/2);
    list<Enemy*> enemigos = game::Instance()->getAllEnemies();
    int i = 0;
    for (Enemy *enemigo : enemigos) {
        if(enemyHealthBars.size() > 0)
        {
            enemyHealthBars[i]->setPosition(enemigo->getInterpolatedPos().x, enemigo->getInterpolatedPos().y - 50);
            borde.setPosition(enemigo->getInterpolatedPos().x, enemigo->getInterpolatedPos().y - 50);
            eng->getApp().draw(borde);
            eng->getApp().draw(*enemyHealthBars[i]);
            i++;       
        }
    }
    int cont = 0;
    if(vecesMejora1 > 0)
    {
        txtHealth.setPosition(Vector2f(825.f + separacion*cont, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 50));
        eng->getApp().draw(txtHealth);
        spritesMejoras[0]->setPosition(Vector2f(875.f + separacion*cont ,eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 60));
        eng->getApp().draw(*spritesMejoras[0]);
        cont++;
    }
    if(vecesMejora2 > 0)
    {
        txtMovSpeed.setPosition(Vector2f(825.f + separacion*cont, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 50));
        eng->getApp().draw(txtMovSpeed);
        spritesMejoras[1]->setPosition(Vector2f(875.f + separacion*cont, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 60));
        eng->getApp().draw(*spritesMejoras[1]);
        cont++;
    }
    if(vecesMejora3 > 0)
    {
        txtAttackSpeed.setPosition(Vector2f(825.f + separacion*cont, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 50));
        eng->getApp().draw(txtAttackSpeed);
        spritesMejoras[2]->setPosition(Vector2f(875.f + separacion*cont, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 60));
        eng->getApp().draw(*spritesMejoras[2]);
        cont++;
    }
    if(vecesMejora4 > 0)
    {
        txtAttackMore.setPosition(Vector2f(825.f + separacion*cont, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 50));
        eng->getApp().draw(txtAttackMore);
        spritesMejoras[3]->setPosition(Vector2f(875.f + separacion*cont, eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 60));
        eng->getApp().draw(*spritesMejoras[3]);
        cont++;
    }

}


