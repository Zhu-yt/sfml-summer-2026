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
        void handleRealtimeInput();
        void update(sf::Time dt);
        void render();

    private:
        enum class State{
            Menu,
            Playing,
            GameOver
        };
        State mState;

        sf::RenderWindow mWindow;
        World mWorld;

        sf::Font mFont;
        sf::Text mMenuText;
        sf::Text mGameOverText;
};

#endif // GAME_HPP