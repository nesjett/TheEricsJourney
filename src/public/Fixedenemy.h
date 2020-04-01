#include <Enemy.h>
#include <Projectile.h>
#include <Player.h>

using namespace std;
using namespace sf;

class Fixedenemy: public Enemy{
    public:
        Fixedenemy();
        void Init();
        bool Attack();
        void Shot(Projectile* proj,Player* player);
        sf::Clock relojMark;

    private:
        string texture_file;
};