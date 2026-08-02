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
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void handleRealtimeInput();

    private:
        sf::RenderWindow mWindow;
        World mWorld;

        bool mIsMovingLeft = false;
        bool mIsMovingRight = false;
        bool mIsMovingUp = false;
        bool mIsMovingDown = false;
};

#endif // GAME_HPP