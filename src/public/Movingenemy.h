#include <Enemy.h>

using namespace std;
using namespace sf;

class Movingenemy: public Enemy{
    public:
        Movingenemy();
        void Init();
        float enemydirection_y;
        float enemydirection_x;
        void Linealmove_y(float pos1, float pos2);
        void Linealmove_x(float pos1, float pos2);

        void Update(float delta);
        void Draw(double percent, double delta );

 
    private:
        string texture_file;
};