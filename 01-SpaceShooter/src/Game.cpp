#include "Game.hpp"
#include <iostream>

const float Game::PlayerSpeed = 300.f;

Game::Game()
: mWindow(sf::VideoMode(800, 600), "Space Shooter - Week 1")
, mIsMovingLeft(false)
, mIsMovingRight(false)
, mIsMovingUp(false)
, mIsMovingDown(false)
{
    mWindow.setFramerateLimit(60);

    //使用 ResourceHolder 加载纹理
    mTextures.load(Textures::Player, "assets/textures/player.png");

    mPlayer.setTexture(mTextures.get(Textures::Player));
    mPlayer.setPosition(336.f, 472.f); //飞机起始放在底部中间
}

void Game::run(){
    sf::Clock clock;

    while(mWindow.isOpen()){
        processEvents();

        sf::Time deltaTime = clock.restart();

        update(deltaTime);
        render();
    }
}

void Game::processEvents(){
    //事件处理
    sf::Event event;
    while(mWindow.pollEvent(event)){
        switch(event.type){
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::A){
                    mIsMovingLeft = true;
                }
                if(event.key.code == sf::Keyboard::D){
                    mIsMovingRight = true;
                }
                if(event.key.code == sf::Keyboard::W){
                    mIsMovingUp = true;
                }
                if(event.key.code == sf::Keyboard::S){
                    mIsMovingDown = true;
                }
                break;
            
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::A){
                    mIsMovingLeft = false;
                }
                if(event.key.code == sf::Keyboard::D){
                    mIsMovingRight = false;
                }
                if(event.key.code == sf::Keyboard::W){
                    mIsMovingUp = false;
                }
                if(event.key.code == sf::Keyboard::S){
                    mIsMovingDown = false;
                }
                break;

            case sf::Event::Closed:
                mWindow.close();
                break;

        }
    }
}

void Game::update(sf::Time deltaTime){
    //移动逻辑
    float dt = deltaTime.asSeconds();

    if(mIsMovingLeft){
        mPlayer.move(-PlayerSpeed * dt, 0.f);
    }
    if(mIsMovingRight){
        mPlayer.move(PlayerSpeed * dt, 0.f);
    }
    if(mIsMovingUp){
        mPlayer.move(0.f, -PlayerSpeed * dt);
    }
    if(mIsMovingDown){
        mPlayer.move(0.f, PlayerSpeed * dt);
    }

    //边界限制
    sf::Vector2f pos = mPlayer.getPosition();

    if(pos.x < -31.f){
        pos.x = -31.f;
    }
    if(pos.x > 800.f - 97.f){
        pos.x = 800.f - 97.f;
    }
    if(pos.y < 0.f){
        pos.y = 0.f;
    }
    if(pos.y > 600.f - 79.f){
        pos.y = 600.f - 79.f;
    }

    mPlayer.setPosition(pos);
}

void Game::render(){
    //渲染
    mWindow.clear(sf::Color::Black);
    mWindow.draw(mPlayer);
    mWindow.display();
}