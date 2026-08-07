#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "Aircraft.hpp"
#include "CommandQueue.hpp"

class World{
    public:
        explicit World(sf::RenderWindow& window);

        CommandQueue& getCommandQueue();

        void update(sf::Time dt);
        void draw();
        void reset();
        bool isGameOver() const {return mGameOver;};
        void setShooting(bool shooting) {mIsShooting = shooting;}
        int getScore() const {return mScore;}

    private:
        void loadTextures();
        void buildScene();
        void spawnEnemy();
        void shoot();
        void onCommand(const Command& command, sf::Time dt);

    private:
        sf::RenderWindow& mWindow;
        sf::Font mFont;
        sf::Text mScoreText;
        ResourceHolder<sf::Texture, Textures::ID> mTextures;
        
        std::unique_ptr<Aircraft> mPlayer;
        std::vector<std::unique_ptr<Aircraft>> mEnemies;

        std::vector<sf::RectangleShape> mBullets;

        CommandQueue mCommandQueue;

        bool mIsShooting;

        sf::Clock mSpawnClock;
        sf::Clock mShootClock;

        static const float PlayerSpeed;
        static const float ShootCooldown;
        static const float SpawnCooldown;

        int mScore;
        int mPlayerHP;
        int mMaxHP;
        sf::RectangleShape mHPBarBackground;
        sf::RectangleShape mHPBar;

        bool mGameOver;
};

#endif //WORLD_HPP