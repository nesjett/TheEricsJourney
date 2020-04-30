#pragma once
#ifndef FIREEXP_H
#define FIREEXP_H
#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <Engine.h>
#include <vector>
#include <iostream>

using namespace sf;

class Fireball_Explosion : public Cascade{

  public:
    Fireball_Explosion();
    virtual ~Fireball_Explosion();

	void Init();

    
  private:
  protected:
};

#endif