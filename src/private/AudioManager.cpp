#include "AudioManager.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

AudioManager* AudioManager::unicaInstancia = 0;

/*Para utilizarlo:

    AudioManager *audio = AudioManager::getInstance();
    AudioManager::getInstance()->respirar();

*/
AudioManager::AudioManager()
{
    menu_music.openFromFile("./resources/audio/menutheme.ogg");
    menu_music.setLoop(true);
    // nivel1_music.openFromFile("sounds/nivel1.ogg");
    // nivel1_music.setLoop(true);
}

AudioManager::~AudioManager()
{
    //dtor
}
void AudioManager::menu()
{
    if (menu_music.getStatus() == SoundSource::Stopped)
        menu_music.play();
    else {
        menu_music.stop();
    }
}
void AudioManager::play_music_menu()
{
    menu_music.play();
}
void AudioManager::stop_music_menu()
{
    menu_music.stop();
}
