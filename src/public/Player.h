#pragma once
#include <Pawn.h>
#include <Enemy.h>
#include <list>

using namespace std;
using namespace sf;

class Player:  public Pawn{
    public:
        Player();
        void TakeDamage(float damage, Actor* dmgCauser, string damage_type);
        bool IsAlive(); // This should go to an interface or to parent PAWN class
        void Init();
        // Adds movement to the desired direction
        void Movimiento(sf::Vector2f pos);
        void setDirection(float x, float y);
        sf::Vector2f getDirection();
        void Attack();
        void Update(float delta);
        void ActorOverlap(Actor otherActor);
        void Draw(double percent, double delta);
        void setHealthMax(float increase);
        void setCurrentH(float increase);
        float getCurrentHealth();
        float getMaxHealth();
        void improvesAttack();
        int GetAttackImprove();
        void ModifyDamage();
        void IncreaseDamageArrows();
        void ModifyCritic(float cri);
        float GetCritic();
        int DireccionPausa();//get the player's direction to the enemy
        void SetAnimation();
        void ToggleMovementIndicator();
        void setGodMode(bool god);
        Enemy* FindClosestEnemy();

        Enemy* GetTarget() { return Target; };
        void ClearTarget() { Target = nullptr; };
        
        float cadenciaMultiplier = 1.f; //This variable multiplies the condition of shooting clock
    protected:
        
        void SetTarget(Enemy *NewTarget);

    private:
        void PrepareSprite();
        void PrepareMovementIndicator();
        string texture_file;
        int AttackImprovement;
        int IncreaseDamage;
        Enemy *Target;
        int LastAttack; // Used to select the sound to play for shooting
        SSprite *MovementIndicator;
        bool GodMode = false;
        sf::Vector2f dir_unit;
        sf::Clock relojAtaque;
        float Critic = 1.f;
        
};