#pragma once
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

    //Audio del menu
    void menu();
    void play_menu_ok();
    void play_menu_move();

    //Audio del juego
    void play_player_shot();
    void play_enemy1_takedamage();
    void play_enemy1_death();

    void PlaySound2D(string File);

protected:
private:
    AudioManager();
    static AudioManager *unicaInstancia;

    //Audio del menu
    Music menu_music, menu_move, menu_ok;

    //Audio del jugador
    Music player_shot;

    //Audio de los enemigos
    Music enemy1_takedamage, enemy1_death;
};

#endif // AUDIOMANAGER_H