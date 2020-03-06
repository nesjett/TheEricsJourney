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