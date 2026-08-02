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
            handleRealtimeInput();
            mWorld.update(TimePerFrame);
        }

        mWorld.draw();
    }
}

void Game::processEvents(){
    //事件处理
    sf::Event event;
    while(mWindow.pollEvent(event)){
        switch (event.type)
        {
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;

        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        
        case sf::Event::Closed:
            mWindow.close();
            break;
        }
    }
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
    if(key == sf::Keyboard::A){
        mIsMovingLeft = isPressed;
    }
    if(key == sf::Keyboard::D){
        mIsMovingRight = isPressed;
    }
    if(key == sf::Keyboard::W){
        mIsMovingUp = isPressed;
    }
    if(key == sf::Keyboard::S){
        mIsMovingDown = isPressed;
    }

    if(key == sf::Keyboard::Space){
        mWorld.setShooting(isPressed);
    }
}

void Game::handleRealtimeInput(){
    Command moveCommand;
    moveCommand.category = Category::PlayerAircraft;

    bool left = mIsMovingLeft;
    bool right = mIsMovingRight;
    bool up = mIsMovingUp;
    bool down = mIsMovingDown;

    moveCommand.action = [left, right, up, down](Entity& entity, sf::Time){
        sf::Vector2f velocity(0.f, 0.f);

        if(left){
            velocity.x -= 300.f;
        }
        if(right){
            velocity.x += 300.f;
        }
        if(up){
            velocity.y -= 300.f;
        }
        if(down){
            velocity.y += 300.f;
        }

        entity.setVelocity(velocity);
    };

    mWorld.getCommandQueue().push(moveCommand);
}