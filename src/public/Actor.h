#pragma once
#ifndef Actor_H
#define Actor_H
#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <Engine.h>
#include <vector>
#include <iostream>

using namespace sf;

class Actor {

  public:
    Actor();
    virtual ~Actor();
    Vector2f getActorLocation() {return location;}
		Vector2f getBoundingBox() {return boundingBox;}
		void setActorLocation(Vector2f loc) {location_prev = location; location = loc;}
    void setActorLocation(Vector2f loc, bool teleport) {if(teleport) { location_prev = location = loc; } else { setActorLocation(loc); }}
		void setBoundingBox(Vector2f wh) {boundingBox = wh;}
		virtual void Update(float delta);
		virtual void Draw(float percent);
		virtual void Init();
    bool isAsleep() {return asleep;}
    void setAsleep(bool newAsleep) {asleep = newAsleep;}

  private:
    bool debug;

  protected:
    bool asleep;
    Vector2f location_prev;
    Vector2f location;
    Vector2f boundingBox;
};

#endif