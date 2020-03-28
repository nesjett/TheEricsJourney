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
	  FloatRect getBoundingBox() {return sprite->getSprite().getGlobalBounds();}
		void moveTo(Vector2f loc) {location_prev = location; location = loc;}
    void setActorLocation(Vector2f loc) { location_prev = location = loc; }
		//void setBoundingBox(IntRect rs) {boundingBox = rs;} // TODO: In the future we should be able to modify bounding box on demand.
    bool isAsleep() {return asleep;};
    void setAsleep(bool newAsleep) {asleep = newAsleep;};
    Vector2f getActorLastLocation() { return location_prev; }

    virtual void Update(float delta);
		virtual void Draw(double percent, double delta );
		virtual void Init();
    virtual void TakeDamage(float damage, string damage_type);
    virtual void ActorOverlap(Actor otherActor);
  private:
    bool debug;
    Vector2f location_prev;
    Vector2f location;
    //IntRect boundingBox;
    sf::Font font;

  protected:
    bool asleep;
    SSprite *sprite;
};

#endif