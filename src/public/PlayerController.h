#include <Controller.h>
#include <Player.h>

#include <SFML/Graphics.hpp>

class PlayerController{

    public:
        PlayerController(Player*);
        //void Update(sf::Vector2f, bool, Player*);
        void Update(sf::Keyboard::Key, bool);
    protected:
        virtual ~PlayerController(); 
    private: 
        sf::Vector2f stop;
        Player* miJugador;

};