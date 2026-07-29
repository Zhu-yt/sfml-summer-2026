#include "World.hpp"

const float World::PlayerSpeed = 300.f;

World::World(sf::RenderWindow& window)
:mWindow(window)
,mIsMovingLeft(false)
,mIsMovingRight(false)
,mIsMovingUp(false)
,mIsMovingDown(false)
,mIsShooting(false){
    loadTextures();
    buildScene();
}

void World::loadTextures(){
    mTextures.load(Textures::Player, "assets/textures/player.png");
}

void World::buildScene(){
    mPlayer.setTexture(mTextures.get(Textures::Player));
    mPlayer.setPosition(336.f, 472.f);
}

void World::handleEvent(const sf::Event& event){
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
            if(event.key.code == sf::Keyboard::Space){
                mIsShooting = true;
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
            if(event.key.code == sf::Keyboard::Space){
                mIsShooting = false;
            }
            break;

        case sf::Event::Closed:
            mWindow.close();
            break;

    }
}

void World::update(sf::Time dt){
    float delta = dt.asSeconds();

    if(mIsMovingLeft){
        mPlayer.move(-PlayerSpeed * delta, 0.f);
    }
    if(mIsMovingRight){
        mPlayer.move(PlayerSpeed * delta, 0.f);
    }
    if(mIsMovingUp){
        mPlayer.move(0.f, -PlayerSpeed * delta);
    }
    if(mIsMovingDown){
        mPlayer.move(0.f, PlayerSpeed * delta);
    }
    if(mIsShooting){
        shoot();
    }

    //子弹移动
    for(auto& bullet : mBullets){
        bullet.move(0.f, -500.f * delta);
    }

    //销毁子弹
    mBullets.erase(
        std::remove_if(mBullets.begin(), mBullets.end(), 
            [](const sf::RectangleShape& b){
                return b.getPosition().y < -10.f;
            }),
        mBullets.end()
    );

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

void World::draw(){
    mWindow.clear(sf::Color::Black);

    mWindow.draw(mPlayer);
    for(const auto& bullet : mBullets){
        mWindow.draw(bullet);
    }

    mWindow.display();
}

void World::shoot(){
    //检查冷却
    if(mShootClock.getElapsedTime().asSeconds() < ShootCooldown){
        return;
    }

    mShootClock.restart();

    //创建子弹
    sf::RectangleShape bullet(sf::Vector2f(4.f, 15.f));
    bullet.setFillColor(sf::Color::White);

    //从飞机正上方发射
    sf::Vector2f playerPos = mPlayer.getPosition();
    bullet.setPosition(playerPos.x + 62.f, playerPos.y);

    mBullets.push_back(bullet);
}