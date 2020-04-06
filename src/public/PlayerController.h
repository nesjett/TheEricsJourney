#include <Controller.h>
#include <Player.h>

#include <SFML/Graphics.hpp>

class PlayerController:  public Controller{

    public:
        PlayerController(Player*);
        //void Update(sf::Vector2f, bool, Player*);
        void Update(sf::Keyboard::Key, bool);

        void setPlayer(Player*);
        void setLista(list<Enemy*>);
        void Attacks();
        void Frenar(sf::Keyboard::Key);


    protected:
        virtual ~PlayerController(); 
    private: 
        sf::Vector2f stop;
        Player* miJugador;

};