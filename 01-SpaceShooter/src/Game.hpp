#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>

class Game{
    public:
        Game();
        void run();

    private:
        void processEvents();
        void update(sf::Time deltaTime);
        void render();

        sf::RenderWindow mWindow;

        sf::Texture mPlayerTexture;
        sf::Sprite mPlayer;

        bool mIsMovingLeft;
        bool mIsMovingRight;
        bool mIsMovingUp;
        bool mIsMovingDown;

        static const float PlayerSpeed;

};

#endif // GAME_HPP