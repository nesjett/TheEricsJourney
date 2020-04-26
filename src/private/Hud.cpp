#include "../public/Hud.h"

Hud* Hud::pInstance = NULL;
Hud* Hud::Instance() {
    if(pInstance == NULL) { // If not created earlier, create a new instance and return it
        pInstance = new Hud;
    } 
    return pInstance;
}
Hud::Hud()
{
    percent = 1;
    width = 200.0;
    height = 25.0;
    colorHealth100 = sf::Color(0, 204, 102);
    colorHealthLess50 = sf::Color(255, 255, 102);
    colorHealthLess25 = sf::Color(255, 0, 0);
    playerHealth.setPosition(Vector2f(850,50));
    playerHealth.setSize(sf::Vector2f(width, height));
    playerHealth.setFillColor(colorHealth100);
    eng = Engine::Instance();
    maxHealth = 0.f;
    currentHealth = 0.f;
    fontHud.loadFromFile("./resources/typos/BenguiatBold.ttf");
    txtHealth.setFont(fontHud);
    txtHealth.setPosition(850,25);
    txtHealth.setCharacterSize(20);
    txtHealth.setString("Health");
}
Hud::~Hud()
{
    
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

void Hud::Draw()
{
    eng->getApp().draw(txtHealth);
    eng->getApp().draw(playerHealth);
}


