#include <Enemy.h>
#include <Projectile.h>
#include <Player.h>

using namespace std;
using namespace sf;

class Explosionenemy: public Enemy{
    public:
        Explosionenemy();
        void Init();
        bool Attack();
        void Shot(Projectile* proj,Player* player);
        sf::Clock relojMark;

    private:
        string texture_file;
};