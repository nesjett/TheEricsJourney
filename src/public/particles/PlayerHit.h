#pragma once
#ifndef PLAYERHIT_H
#define PLAYERHIT_H
#include <string>
#include <Engine.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayerHit : public Cascade{

  public:
    PlayerHit(Vector2f Loc);
    virtual ~PlayerHit();


    
  private:
  protected:
};

#endif