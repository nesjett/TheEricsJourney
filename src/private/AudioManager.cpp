#include "AudioManager.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

AudioManager* AudioManager::unicaInstancia = 0;

AudioManager::AudioManager()
{
    //Cargamos todos los sonidos
    //Menu
    menu_music.openFromFile("./resources/audio/main_theme.ogg");
    menu_music.setLoop(true);
    menu_move.openFromFile("./resources/audio/cursor_move.ogg");
    menu_ok.openFromFile("./resources/audio/cursor_ok.ogg");
    menu_ok.setPitch(2);
    menu_move.setPitch(2);
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
    while(menu_ok.getStatus() == SoundSource::Playing){} //Hasta que no se reproduzca por completo no se sigue
}


shared_ptr<Music> AudioManager::PlaySound2D(string File){

    // security remove olds
    if(SoundQueue.size() > 100) {
        std::vector<decltype(SoundQueue)::value_type>(SoundQueue.begin()+90, SoundQueue.end()).swap(SoundQueue);
    }


    SoundQueue.push_back(make_shared<Music>());
    shared_ptr<Music> ref = SoundQueue.back();
    ref->openFromFile(File);

    // Adjust random pitch to be between 0.75 and 1.25
    float rp = 0.75 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.25-0.75))); // Rnadom pitch in range
    ref->setPitch(rp);
    ref->setVolume(100.f);
    ref->play();
    return ref;
}
