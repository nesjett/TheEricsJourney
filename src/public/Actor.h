#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Actor {

  public:
    Actor();
    Vector2f getActorLocation() {return location;}
		Vector2f getBoundingBox() {return boundingBox;}
		void setActorLocation(Vector2f loc) {location = loc;}
		void setBoundingBox(Vector2f wh) {boundingBox = wh;}
		void update();
		void draw();
		void setup();

  private:
    Vector2f location;
    Vector2f boundingBox;
};