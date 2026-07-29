#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class World{
    public:
        World(sf::RenderWindow& window);

        void handleEvent(const sf::Event& event);
        void update(sf::Time dt);
        void draw();

    private:
        void loadTextures();
        void buildScene();
        void shoot();

    private:
        sf::RenderWindow& mWindow;
        ResourceHolder<sf::Texture, Textures::ID> mTextures;
        sf::Sprite mPlayer;

        bool mIsMovingLeft;
        bool mIsMovingRight;
        bool mIsMovingUp;
        bool mIsMovingDown;

        std::vector<sf::RectangleShape> mBullets;
        sf::Clock mShootClock;
        const float ShootCooldown = 0.2f;
        bool mIsShooting;

        static const float PlayerSpeed;
};

#endif //WORLD_HPP