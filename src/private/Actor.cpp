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
    game *gi = game::Instance();

    long gameTime = gi->getTime();
    lifeSpan = gi->getTime() + t1.asMilliseconds(); // Define exact time at which the actor should be destroyed
    //std::cout << "Game time: " << gameTime << " Destroy time: " << lifeSpan << std::endl;
}
