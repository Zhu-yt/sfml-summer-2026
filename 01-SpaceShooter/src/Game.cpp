#include "Game.hpp"
#include <iostream>

Game::Game()
: mWindow(sf::VideoMode(800, 600), "Space Shooter - Week 1")
, mWorld(mWindow)
, mState(State::Menu)
{
    mWindow.setFramerateLimit(60);

    mFont.loadFromFile("assets/fonts/Sansation.ttf");

    mMenuText.setFont(mFont);
    mMenuText.setString("SPACE SHOOTER\n\nPress Enter to Start");
    mMenuText.setCharacterSize(40);
    mMenuText.setFillColor(sf::Color::White);
    mMenuText.setStyle(sf::Text::Bold);

    sf::FloatRect bounds = mMenuText.getLocalBounds();
    mMenuText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    mMenuText.setPosition(400.f, 300.f);

    mGameOverText.setFont(mFont);
    mGameOverText.setCharacterSize(40);
    mGameOverText.setFillColor(sf::Color::Red);
    mGameOverText.setStyle(sf::Text::Bold);
    mGameOverText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    mGameOverText.setPosition(400.f, 250.f);
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
            
            if(mState == State::Playing){
                handleRealtimeInput();

                mWorld.update(TimePerFrame);

                if(mWorld.isGameOver()){
                    mState = State::GameOver;

                    mGameOverText.setString("GAME OVER\nScore: " 
                    + std::to_string(mWorld.getScore()) 
                    + "\n\nPress R to Restart");

                    sf::FloatRect bounds = mGameOverText.getLocalBounds();
                    mGameOverText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
                }
            }
        }

        render();
    }
}

void Game::processEvents(){
    //事件处理
    sf::Event event;
    while(mWindow.pollEvent(event)){
        if(event.type == sf::Event::Closed){
            mWindow.close();
            return;
        }

        switch(mState){
            case State::Menu:
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Return){
                    mState = State::Playing;
                }
                break;

            case State::Playing:
                break;

            case State::GameOver:
                if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R){
                    mWorld.reset();

                    mState = State::Playing;
                }
                break;
                
        }
    }
}

void Game::handleRealtimeInput(){
    if(mState != State::Playing){
        return;
    }

    Command moveCommand;
    moveCommand.category = Category::PlayerAircraft;

    bool left = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    bool right = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
    bool up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    bool down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

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

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        mWorld.setShooting(true);
    }else{
        mWorld.setShooting(false);
    }
}

void Game::render(){
    mWindow.clear(sf::Color::Black);

    switch(mState){
        case State::Menu:
            mWindow.draw(mMenuText);
            break;
        
        case State::Playing:
            mWorld.draw();
            break;

        case State::GameOver:
            mWorld.draw();
            mWindow.draw(mGameOverText);
            break;
    }

    mWindow.display();
}