#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>

using namespace std;


class Engine
{
    public:
        static Engine* Instance();
        void init(/*char*, int*/);
    protected:
        Engine();
        Engine(const Engine &);
        Engine &operator= (const Engine &);
        virtual ~Engine();
    private:
};


#endif 