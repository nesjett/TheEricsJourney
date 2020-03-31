#include <Controller.h>
#include <Player.h>

#include <SFML/Graphics.hpp>

class PlayerController{

    public:
        PlayerController(Player*);
        //void Update(sf::Vector2f, bool, Player*);
        void Update(bool, sf::Keyboard::Key);
    protected:
        virtual ~PlayerController(); 
    private: 
        sf::Vector2f pos1;
        sf::Vector2f pos2;
        sf::Vector2f pos3;
        sf::Vector2f pos4;
        sf::Vector2f stop;
        sf::Vector2f directionAux;
        Player* miJugador;

};