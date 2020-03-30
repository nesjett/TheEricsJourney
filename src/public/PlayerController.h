#include <Controller.h>
#include <SFML/Graphics.hpp>

using namespace std;

class PlayerController :  public Controller{
    public:
        PlayerController();
        void Update(sf::Vector2f);

    protected:
        virtual ~PlayerController();

    private:
        bool prueba = false;
        

};