#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <SFML/System.hpp>
#include <iostream>



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

    void menu();
    void play_music_menu();
    void stop_music_menu();

protected:
private:
    AudioManager();
    static AudioManager *unicaInstancia;
    Music menu_music;
};

#endif // AUDIOMANAGER_H