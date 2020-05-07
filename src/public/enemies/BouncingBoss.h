#pragma once
#include <Enemy.h>
#include "game.h"

using namespace std;
using namespace sf;

class BouncingBoss: public Enemy{
    public:
        BouncingBoss();
        BouncingBoss(Vector2f Dir, int Childrens, float Scale, float MaxHealth);
        virtual ~BouncingBoss();
        void Init();
        void PrepareSprite();
        void Update(float delta);
        void Draw(double percent, double delta );
        void TakeDamage(float damage, Actor* dmgCauser, string damage_type);
        void OnActorOverlap(Actor *otherActor);

        void RandomDeviateDirectionInRange(Vector2f Direction, float Debiation);

    protected:
        void Die();

    private:
        string texture_file;
        long DmgCooldownEndTime = -1;
        long DmgAnimationEndTime = -1;
        sf::Clock InternalClock;

        long TimeDmgAnimation = 500; // Time to show the hit animation in ms
        long TimeBetweenAttacks = 2500; // Time between one "attack" and the next

        /*  Amount of children actors to spawn on death. Defaults to 0 */
        int NbrChildren;

        // from 1 to > 0
        float SpriteScale;
};