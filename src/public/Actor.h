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
	  FloatRect getBoundingBox() {return sprite->getGlobalBounds();}

    /*/////////////////////////////////////////////////////////
    \brief Updates de current and old locations

    This function is used to move an actor to a new position. 
    The loc parameter must be a close location or blinking issues will 
    appear, usually as result of multiplying direction*movementSpeed*delta time. 
    Draw loop will interpolate between those current and old locations 
    to draw the actor movement smoothly.

    \param loc Vector2f with the new location.

    /////////////////////////////////////////////////////////*/
		void UpdateMovement(Vector2f loc) {location_prev = location; location = loc;}
    void setActorLocation(Vector2f loc) { location_prev = location = loc; }
		//void setBoundingBox(IntRect rs) {boundingBox = rs;} // TODO: In the future we should be able to modify bounding box on demand.
    bool isAsleep() {return asleep;};
    void setAsleep(bool newAsleep) {asleep = newAsleep;};
    Vector2f getActorLastLocation() { return location_prev; };
    ObjectType getObjectType(){return oType; };

    virtual void Update(float delta);
		virtual void Draw(double percent, double delta );
		virtual void Init();
    virtual void TakeDamage(float damage, Actor* dmgCauser, string damage_type);

    bool debug;
    bool debug_coords;
  
  /*/////////////////////////////////////////////////////////
  \brief Fires when the actor is overlapped by another actor

  This function fires when OTHER actors overlap It. This means
  you get the overlap event when a projectile hits this actor,
  but the projectile will receive another overlap when the current
  actor overlaps with the projectile. Projectile should apply damage
  when It is overlapped, not when other are overlapped by It.

  \param otherActor Actor that overlapped us

  /////////////////////////////////////////////////////////*/
    virtual void OnActorOverlap(Actor *otherActor);


  /*///////////////////////////
    \brief Sets the remaining life time for the object

    The method calculates the time in millesconds at which the object
    must be destroyed, adding the desired seconds to the time elapsed
    since the game begin.

    \param secs Float with the time in seconds reamining to die

  ///////////////////////////*/
    void setLifespan(float secs);

    // Returns whether the actor is pending delete or not
    bool IsValid() { return pendingDelete; };
    bool pendingDelete = false;

  private:
    Vector2f location_prev;
    Vector2f location;
    //IntRect boundingBox;
    sf::Font font;

  protected:
    bool asleep;
    SSprite *sprite;
    ObjectType oType; // Object type for collision channel
    long lifeSpan = -1;
    Vector2f currentLoc;
};

#endif