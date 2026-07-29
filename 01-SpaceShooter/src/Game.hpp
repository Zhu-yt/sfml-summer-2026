#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "World.hpp"

class Game{
    public:
        Game();
        void run();

    private:
        void processEvents();

    private:
        sf::RenderWindow mWindow;
        World mWorld;
};

#endif // GAME_HPP