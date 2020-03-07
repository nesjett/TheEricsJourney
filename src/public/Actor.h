#pragma once
#include <string>
#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

class Actor {

  public:
    Actor();
    virtual ~Actor();
    Vector2f getActorLocation() {return location;}
		Vector2f getBoundingBox() {return boundingBox;}
		void setActorLocation(Vector2f loc) {location_prev = location; location = loc;}
		void setBoundingBox(Vector2f wh) {boundingBox = wh;}
		virtual void Update(float delta);
		virtual void Draw(sf::RenderWindow &window, float percent);
		virtual void Init();
    bool isAsleep() {return asleep;}
    void setAsleep(bool newAsleep) {asleep = newAsleep;}

  private:
    

  protected:
    bool asleep;
    Vector2f location_prev;
    Vector2f location;
    Vector2f boundingBox;
};