#pragma once
#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <SFML/System.hpp>
#include <iostream>
#include <memory>



using namespace std;
using namespace sf;

class AudioManager
{
public:
    static AudioManager *getInstance()
    {
        if (unicaInstancia == 0)
            unicaInstancia = new AudioManager();
        return unicaInstancia;
    }
    virtual ~AudioManager();

    //Audio del menu
    void menu();
    void play_menu_ok();
    void play_menu_move();



    // Fire and forget sound. Keeps track of all in a sound queue.
    shared_ptr<Music> PlaySound2D(string File);

protected:
private:
    AudioManager();
    static AudioManager *unicaInstancia;

    //Audio del menu
    Music menu_music, menu_move, menu_ok;

    vector<std::shared_ptr<Music>> SoundQueue;
};

#endif // AUDIOMANAGER_H