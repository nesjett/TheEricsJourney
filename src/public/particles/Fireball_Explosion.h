#pragma once
#ifndef FIREEXP_H
#define FIREEXP_H
#include <string>
#include <Engine.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class Fireball_Explosion : public Cascade{

  public:
    Fireball_Explosion(Vector2f Loc);
    virtual ~Fireball_Explosion();


    
  private:
  protected:
};

#endif