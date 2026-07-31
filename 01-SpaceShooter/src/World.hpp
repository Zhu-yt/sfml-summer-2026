#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Aircraft.hpp"

class World{
    public:
        explicit World(sf::RenderWindow& window);

        void handleEvent(const sf::Event& event);
        void update(sf::Time dt);
        void draw();

    private:
        void loadTextures();
        void buildScene();
        void spawnEnemy();
        void shoot();

    private:
        sf::RenderWindow& mWindow;
        sf::Font mFont;
        sf::Text mScoreText;
        ResourceHolder<sf::Texture, Textures::ID> mTextures;
        
        std::unique_ptr<Aircraft> mPlayer;
        std::vector<std::unique_ptr<Aircraft>> mEnemies;

        std::vector<sf::RectangleShape> mBullets;

        bool mIsMovingLeft;
        bool mIsMovingRight;
        bool mIsMovingUp;
        bool mIsMovingDown;
        bool mIsShooting;

        sf::Clock mSpawnClock;
        sf::Clock mShootClock;

        static const float PlayerSpeed;
        static const float ShootCooldown;
        static const float SpawnCooldown;

        int mScore;
};

#endif //WORLD_HPP