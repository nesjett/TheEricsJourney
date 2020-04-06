#include <Pawn.h>

using namespace std;
using namespace sf;

class Skeleton: public Pawn {
    public:
        Skeleton();
        void Draw(double percent, double delta );
    protected:
        void PrepareSprite();
        Animation* animation;
    private:
        string texture_file;
};