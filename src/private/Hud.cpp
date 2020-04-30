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
    height = 5.f;
    colorHealth100 = sf::Color(0, 204, 102);
    colorHealthLess50 = sf::Color(255, 255, 102);
    colorHealthLess25 = sf::Color(255, 0, 0);
    playerHealth.setPosition(Vector2f(850,eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 50));
    playerHealth.setSize(sf::Vector2f(width, height));
    playerHealth.setFillColor(colorHealth100);
    maxHealth = 0.f;
    currentHealth = 0.f;
    fontHud.loadFromFile("./resources/typos/BenguiatBold.ttf");
    txtHealth.setFont(fontHud);
    playerHealth.setPosition(Vector2f(850,eng->getApp().getView().getCenter().y - (eng->getApp().getView().getSize().y/2)+ 25));
    txtHealth.setCharacterSize(20);
    txtHealth.setString("Health");
}
Hud::~Hud()
{
    enemyHealthBars.erase(enemyHealthBars.begin(), enemyHealthBars.end());
}

void Hud::setMaxHealth(float health)
{
    maxHealth = health;
}

void Hud::setCurrentHealth(float health)
{
    if(health >= 0.f)
    {
        currentHealth = health;
    }
    //Update de las variables que dependen de la vida
    percent = currentHealth / maxHealth;
    playerHealth.setSize(sf::Vector2f(percent*width, height));
    playerHealth.setOrigin(width/2, height/2);
    playerHealth.setFillColor(colorHealth100);
    if(percent <= 0.5f && percent > 0.25f)
    {
        playerHealth.setFillColor(colorHealthLess50);
    }
    if(percent <= 0.25f)
    {
        playerHealth.setFillColor(colorHealthLess25);
    }
}

void Hud::setPlayer(Player* player)
{
    jugador = player;
    setMaxHealth(jugador->getMaxHealth());
    setCurrentHealth(jugador->getCurrentHealth());
}

// void Hud::addEnemy(Enemy* enemy)
// {
//     enemigos.push_back(enemy);
//     RectangleShape vidaEnemigo;
//     vidaEnemigo.setSize(sf::Vector2f(width, height));
//     vidaEnemigo.setOrigin(width/2, height/2);
//     vidaEnemigo.setFillColor(colorHealth100);
//     enemyHealthBars.push_back(vidaEnemigo);
// }
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
            enemyHealthBars[i]->setSize(sf::Vector2f(percent*width, height));
            enemyHealthBars[i]->setFillColor(colorHealth100);
            enemyHealthBars[i]->setOrigin(width/2, height/2);
            if(percent <= 0.5f && percent > 0.25f)
            {
                enemyHealthBars[i]->setFillColor(colorHealthLess50);
            }
            if(percent <= 0.25f)
            {
                enemyHealthBars[i]->setFillColor(colorHealthLess25);
            }
            i++;
        }       
    }
    // for(int i = 0; i < enemyHealthBars.size(); i++)
    // {
    //     if(enemigos[i]->health_Current >= 0.f)
    //     {
    //         percent = enemigos[i]->health_Current / enemigos[i]->health_MAX;
    //         enemyHealthBars[i].setSize(sf::Vector2f(percent*width, height));
    //         enemyHealthBars[i].setFillColor(colorHealth100);
    //         if(percent <= 0.5f && percent > 0.25f)
    //         {
    //             enemyHealthBars[i].setFillColor(colorHealthLess50);
    //         }
    //         if(percent <= 0.25f)
    //         {
    //             enemyHealthBars[i].setFillColor(colorHealthLess25);
    //         }
    //     }
    // }
 }

void Hud::Draw()
{
    //Barra de vida del jugador con borde
    playerHealth.setPosition(Vector2f(jugador->getInterpolatedPos().x, jugador->getInterpolatedPos().y - 50));
    RectangleShape borde;
    borde.setSize(sf::Vector2f(width, height));
    borde.setPosition(Vector2f(jugador->getInterpolatedPos().x, jugador->getInterpolatedPos().y - 50));
    borde.setOrigin(width/2, height/2);
    borde.setOutlineColor(sf::Color::Black);
    borde.setOutlineThickness(1);
    borde.setFillColor(Color::Transparent);
    eng->getApp().draw(borde);
    eng->getApp().draw(playerHealth);

    //Barras de vida de los enemigos con borde
    // for(int i = 0; i < enemigos.size(); i++)
    // {
    //     enemyHealthBars[i].setPosition(enemigos[i]->getInterpolatedPos().x, enemigos[i]->getInterpolatedPos().y - 50);
    //     borde.setPosition(enemigos[i]->getInterpolatedPos().x, enemigos[i]->getInterpolatedPos().y - 50);
    //     eng->getApp().draw(borde);
    //     eng->getApp().draw(enemyHealthBars[i]);
    // }
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
}


