#include "AudioManager.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

AudioManager* AudioManager::unicaInstancia = 0;

AudioManager::AudioManager()
{
    //Cargamos todos los sonidos
    //Menu
    menu_music.openFromFile("./resources/audio/menutheme.ogg");
    menu_music.setLoop(true);
    menu_move.openFromFile("./resources/audio/cursor_move.ogg");
    menu_ok.openFromFile("./resources/audio/cursor_ok.ogg");
    menu_ok.setPitch(2);
    menu_move.setPitch(2);

    //Jugador
    player_shot.openFromFile("./resources/audio/player_shot.ogg");
    enemy1_takedamage.openFromFile("./resources/audio/hit.ogg");
    enemy1_death.openFromFile("./resources/audio/enemy1_death.ogg");
    enemy1_takedamage.setPitch(1);
    enemy1_death.setPitch(1);
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

//Audio del juego
void AudioManager::play_player_shot()
{
    player_shot.play();
}
void AudioManager::play_enemy1_takedamage()
{
    //enemy1_takedamage.play();
}
void AudioManager::play_enemy1_death()
{
    //enemy1_death.play();
}

shared_ptr<Music> AudioManager::PlaySound2D(string File){
    SoundQueue.push_back(make_shared<Music>());
    shared_ptr<Music> ref = SoundQueue.back();
    ref->openFromFile(File);
    ref->setVolume(100.f);
    ref->play();
    return ref;
}
