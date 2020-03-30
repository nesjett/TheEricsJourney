#include <Controller.h>
#include <Player.h>

#include <iostream>
#include <list>
#include <iterator>
#include <SFML/Graphics.hpp>
#include <algorithm>

class PlayerController{

    public:
        PlayerController();
        //void Update(sf::Vector2f, bool, Player*);
        void Update(bool, Player*, sf::Keyboard::Key);
    protected:
        virtual ~PlayerController(); 
    private: 
        sf::Vector2f pos1;
        sf::Vector2f pos2;
        sf::Vector2f pos3;
        sf::Vector2f pos4;
        sf::Vector2f stop;
        sf::Vector2f directionAux;

};