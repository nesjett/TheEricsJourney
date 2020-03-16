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
		virtual Rect<float> getBoundingBox() {return boundingBox;}
		void moveTo(Vector2f loc) {location_prev = location; location = loc;}
    void setActorLocation(Vector2f loc) { location_prev = location = loc; }
		void setBoundingBox(Rect<float> rs) {boundingBox = rs;}
		virtual void Update(float delta);
		virtual void Draw(double percent, double delta );
		virtual void Init();
    virtual void TakeDamage(float damage, string damage_type);
    bool isAsleep() {return asleep;};
    void setAsleep(bool newAsleep) {asleep = newAsleep;};
    virtual void ActorOverlap(Actor otherActor);

  private:
    bool debug;

  protected:
    bool asleep;
    Vector2f location_prev;
    Vector2f location;
    Rect<float> boundingBox;
};

#endif