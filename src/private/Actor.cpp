#include "Actor.h"

#include <game.h>

Actor::Actor() {
  //std::cout << "New actor created" << std::endl;
  setActorLocation(Vector2f(0.f,0.f)); 
  //setBoundingBox( sf::IntRect( 0, 0, 0, 0 ) ); // Init bounding box to 0
  oType = worldstatic;
  asleep = false;
  debug = false;

  if(debug){
    font.loadFromFile("./resources/arial.ttf");
  }
}

void Actor::Init(){

}

void Actor::Update(float delta){
  // Check for collisions here in the parent?

  game *gi = game::Instance();
  // CHECK PENDING DESTROY
  if(lifeSpan >= 0.f && gi->getTime() >= lifeSpan) {
    pendingDelete = true;
  }
}

void Actor::Draw(double percent, double delta ){
  if(!sprite) {
    return;
  }

  if(asleep) {
    currentLoc = getActorLocation(); // we have to draw the collision debuggin, but without moving
  } else {
    currentLoc = sprite->Draw(getActorLocation(), getActorLastLocation(), percent); // Location of sprite during interpolation
  }
  if(currentLoc.x == location.x && currentLoc.y == location.y) {
    setActorLocation(location);
  }

  if(!debug){ 
    return;
  }

  FloatRect globalBounds = getBoundingBox();
  sf::RectangleShape rect( Vector2f(globalBounds.width,globalBounds.height) );

  // Show actor bounding box
  rect.setPosition(globalBounds.left,globalBounds.top);
  rect.setFillColor(sf::Color(0,0,0,0));
  rect.setOutlineThickness(1.3);
  rect.setOutlineColor(sf::Color(250, 0, 0));

  // Show actor location
  sf::CircleShape circ( 6.0, 10.0 );
  circ.setPosition(currentLoc.x-6,currentLoc.y-6);
  circ.setFillColor(sf::Color(0,250,0));
  circ.setOutlineColor(sf::Color(0, 250, 0));


  // Show actor location coords
  sf::Text text;
  text.setString("(" + std::to_string(currentLoc.x) + "x, " + std::to_string(currentLoc.y) + "y)");
  text.setFont(font);
  text.setCharacterSize(12); 
  text.setColor(sf::Color::Green);
  text.setStyle(sf::Text::Regular);
  text.setPosition(currentLoc.x+10, currentLoc.y+10); // We add a small offset

  // Show actor bounding box data
  sf::Text text_bounding;
  text_bounding.setString("(" + std::to_string(globalBounds.left) + "x, " + std::to_string(globalBounds.top) + "y, " + std::to_string(globalBounds.width) + "w, " + std::to_string(globalBounds.height) +"h)");
  text_bounding.setFont(font);
  text_bounding.setCharacterSize(12); 
  text_bounding.setColor(sf::Color::Red);
  text_bounding.setStyle(sf::Text::Regular);
  text_bounding.setPosition(globalBounds.left, globalBounds.top-15); // We add a small offset

  // Show actor bounding bottom right corner
  sf::Text text_bounding_corner;
  text_bounding_corner.setString("(" + std::to_string(globalBounds.left+globalBounds.width) + "x, " + std::to_string(globalBounds.top+globalBounds.height) + "y)");
  text_bounding_corner.setFont(font);
  text_bounding_corner.setCharacterSize(12); 
  text_bounding_corner.setColor(sf::Color::Red);
  text_bounding_corner.setStyle(sf::Text::Regular);
  text_bounding_corner.setPosition(globalBounds.left+globalBounds.width, globalBounds.top+globalBounds.height); // We add a small offset

  // Show bounding bottom right corner location
  sf::CircleShape circ_bounding( 4.0, 7.0 );
  circ_bounding.setPosition(globalBounds.left+globalBounds.width-4,globalBounds.top+globalBounds.height-4);
  circ_bounding.setFillColor(sf::Color::Red);
  circ_bounding.setOutlineColor(sf::Color::Red);


  Engine *eng = Engine::Instance();
  eng->getApp().draw(rect); // bounding box
  eng->getApp().draw(circ); // actor location
  if(debug_coords) {
    eng->getApp().draw(text); // actor location
    eng->getApp().draw(text_bounding); // actor bounding box data
    eng->getApp().draw(text_bounding_corner); // actor bounding box corner location
    eng->getApp().draw(circ_bounding); // actor bounding box corner location point
  }
}

void Actor::TakeDamage(float damage, Actor* dmgCauser, string damage_type){

}

void Actor::OnActorOverlap(Actor *otherActor){

}

Actor::~Actor(){
  delete sprite;
}

Vector2f Actor::getInterpolatedPos()
{
  return currentLoc;
}

void Actor::setLifespan(float secs) { 
    sf::Time t1 = sf::seconds(secs);
    lifeSpan = game::Instance()->getTime() + t1.asMilliseconds(); // Define exact time at which the actor should be destroyed
}


/* SWEPT AABB source: https://www.gamedev.net/articles/programming/general-and-gameplay-programming/swept-aabb-collision-detection-and-response-r3084/ */
sf::FloatRect Actor::GetSweptBroadphaseBox(){
  sf::FloatRect b = this->getBoundingBox(); // own actor box
  sf::FloatRect broadphasebox;
  broadphasebox.left = Velocity.x > 0 ? b.left : b.left + Velocity.x;  
  broadphasebox.top = Velocity.y > 0 ? b.top : b.top + Velocity.y;  
  broadphasebox.width = Velocity.x > 0 ? Velocity.x + b.width : b.width - Velocity.x;  
  broadphasebox.height = Velocity.y > 0 ? Velocity.y + b.height : b.height - Velocity.y;  

  return broadphasebox; 
}

bool Actor::AABBCheck(Actor& Other) {
  sf::FloatRect b1 = this->getBoundingBox();
  sf::FloatRect b2 = Other.getBoundingBox();
  return b1.intersects(b2); 
}

float Actor::SweptAABB(Actor& Other, Vector2f& ImpactNormal){
  float xInvEntry, yInvEntry;
  float xInvExit, yInvExit;
  sf::FloatRect OtherBox = Other.getBoundingBox();
  sf::FloatRect OwnBox = this->getBoundingBox();

  // find the distance between the objects on the near and far sides for both x and y
  if (Velocity.x > 0.0f) {
      xInvEntry = OtherBox.left - (OwnBox.left + OwnBox.width);
      xInvExit = (OtherBox.left + OtherBox.width) - OwnBox.left;
  }
  else {
      xInvEntry = (OtherBox.left + OtherBox.width) - OwnBox.left;
      xInvExit = OtherBox.left - (OwnBox.left + OwnBox.width);
  }

  if (Velocity.y > 0.0f) {
      yInvEntry = OtherBox.top - (OwnBox.top + OwnBox.height);
      yInvExit = (OtherBox.top + OtherBox.height) - OwnBox.top;
  }
  else {
      yInvEntry = (OtherBox.top + OtherBox.height) - OwnBox.top;
      yInvExit = OtherBox.top - (OwnBox.top + OwnBox.height);
  }

  // find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
  float xEntry, yEntry;
  float xExit, yExit;

  if (Velocity.x == 0.0f) {
      xEntry = -std::numeric_limits<float>::infinity();
      xExit = std::numeric_limits<float>::infinity();
  }
  else  {
      xEntry = xInvEntry / Velocity.x;
      xExit = xInvExit / Velocity.x;
  }

  if (Velocity.y == 0.0f) {
      yEntry = -std::numeric_limits<float>::infinity();
      yExit = std::numeric_limits<float>::infinity();
  }
  else {
      yEntry = yInvEntry / Velocity.y;
      yExit = yInvExit / Velocity.y;
  }

  // find the earliest/latest times of collision
  // TODO: Is this the correct order..?
  float entryTime = std::max(xEntry, yEntry);
  float exitTime = std::min(xExit, yExit);

  // if there was no collision
  if (entryTime > exitTime || (xEntry < 0.0f && yEntry < 0.0f) || xEntry > 1.0f || yEntry > 1.0f) {
      ImpactNormal.x = 0.0f;
      ImpactNormal.y = 0.0f;
      return 1.0f;
  }
  else{ // There was a collision
      // calculate normal of collided surface
      if (xEntry > yEntry) 
      {
          if (xInvEntry < 0.0f) {
              ImpactNormal.x = 1.0f;
              ImpactNormal.y = 0.0f;
          }
          else {
              ImpactNormal.x = -1.0f;
              ImpactNormal.y = 0.0f;
          }
      }
      else 
      {
          if (yInvEntry < 0.0f) {
              ImpactNormal.x = 0.0f;
              ImpactNormal.y = 1.0f;
          }
          else {
              ImpactNormal.x = 0.0f;
              ImpactNormal.y = -1.0f;
          }
      }

      // return the time of collision
      return entryTime;
  }
}