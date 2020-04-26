#include "AudioManager.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

AudioManager* AudioManager::unicaInstancia = 0;

AudioManager::AudioManager()
{
    //Cargamos todos los sonidos
    menu_music.openFromFile("./resources/audio/menutheme.ogg");
    menu_music.setLoop(true);
    menu_move.openFromFile("./resources/audio/cursor_move.ogg");
    menu_ok.openFromFile("./resources/audio/cursor_ok.ogg");
}

AudioManager::~AudioManager()
{
    //dtor
}

//Audio del menu
void AudioManager::menu()
{
    if (menu_music.getStatus() == SoundSource::Stopped)
        menu_music.play();
    else {
        menu_music.stop();
    }
}
void AudioManager::play_menu_move()
{
    menu_move.play();
}
void AudioManager::play_menu_ok()
{
    menu_ok.play();
}

//Audio del juego
void AudioManager::play_player_shot()
{

}
