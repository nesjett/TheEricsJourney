#pragma once
#ifndef COIN_H
#define COIN_H
#include <string>
#include <Engine.h>
#include <SFML/Graphics.hpp>

using namespace sf;

class Coin : public Cascade{

  public:
    Coin(Vector2f Loc);
    virtual ~Coin();


    
  private:
  protected:
};

#endif