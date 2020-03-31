#include <Enemy.h>

using namespace std;
using namespace sf;

class Fixedenemy: public Enemy{
    public:
        Fixedenemy();
        void Init();

    private:
        string texture_file;
};