#include "../public/Engine.h"

Engine* Engine::pInstance = NULL;
Engine* Engine::Instance() {
    if(pInstance == NULL) { // If not created earlier, create a new instance and return it
        pInstance = new Engine;
    } 
    return pInstance;
}
Engine::Engine()
{

}


