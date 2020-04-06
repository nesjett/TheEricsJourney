#include "../public/Controller.h"

Controller::Controller(){
}

void Controller::Move(float x, float y){
    miJugador->setDirection(x, y);
}

Controller::~Controller() // Destructor
{
 
}