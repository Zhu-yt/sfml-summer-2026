#include "Game.hpp"
#include <iostream>

Game::Game()
: mWindow(sf::VideoMode(800, 600), "Space Shooter - Week 1")
, mWorld(mWindow)
{
    mWindow.setFramerateLimit(60);
}

void Game::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

    while(mWindow.isOpen()){
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        while(timeSinceLastUpdate > TimePerFrame){
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            mWorld.update(TimePerFrame);
        }

        mWorld.draw();
    }
}

void Game::processEvents(){
    //事件处理
    sf::Event event;
    while(mWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            mWindow.close();
        }

        mWorld.handleEvent(event);
    }
}