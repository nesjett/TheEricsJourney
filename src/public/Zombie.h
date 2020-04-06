
#include <Pawn.h>

using namespace std;
using namespace sf;

class Zombie: public Pawn {
    public:
        Zombie();
        void Draw(double percent, double delta );
    protected:
        void PrepareSprite();
        Animation* activeAnim = NULL;
        std::map<std::string, Animation*> Animations;
    private:
        string texture_file;
};