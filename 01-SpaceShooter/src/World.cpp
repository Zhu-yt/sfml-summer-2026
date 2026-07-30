#include "World.hpp"
#include <iostream>

const float World::PlayerSpeed = 300.f;
const float World::ShootCooldown = 0.2f;
const float World::SpawnCooldown = 2.0f;

World::World(sf::RenderWindow& window)
:mWindow(window)
,mIsMovingLeft(false)
,mIsMovingRight(false)
,mIsMovingUp(false)
,mIsMovingDown(false)
,mIsShooting(false)
,mScore(0){
    loadTextures();
    buildScene();
}

void World::loadTextures(){
    mTextures.load(Textures::Player, "assets/textures/player.png");
}

void World::buildScene(){
    mPlayer = std::make_unique<Aircraft>(Aircraft::Type::Player, mTextures);
    mPlayer->setPosition(sf::Vector2f(336.f, 472.f));
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
        mPlayer->move(sf::Vector2f(-PlayerSpeed * delta, 0.f));
    }
    if(mIsMovingRight){
        mPlayer->move(sf::Vector2f(PlayerSpeed * delta, 0.f));
    }
    if(mIsMovingUp){
        mPlayer->move(sf::Vector2f(0.f, -PlayerSpeed * delta));
    }
    if(mIsMovingDown){
        mPlayer->move(sf::Vector2f(0.f, PlayerSpeed * delta));
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

    spawnEnemy();

    for(auto& enemy : mEnemies){
        enemy->update(dt);
    }

    //敌人消失
    mEnemies.erase(
        std::remove_if(mEnemies.begin(), mEnemies.end(), 
            [](const std::unique_ptr<Aircraft>& e){
                return e->getPosition().y > 600.f + 79.f;
        }),
        mEnemies.end()
    );

    //碰撞检测
    for(auto bulletIt = mBullets.begin(); bulletIt != mBullets.end(); ){
        bool hit = false;

        for(auto enemyIt = mEnemies.begin(); enemyIt != mEnemies.end(); ){
            if(bulletIt->getGlobalBounds().intersects((*enemyIt)->getBoundingRect())){
                enemyIt = mEnemies.erase(enemyIt);
                hit = true;
                mScore += 100;
                std::cout << "Score: " << mScore << "\n";
                break;
            }else{
                ++enemyIt;
            }
        }

        if(hit){
            bulletIt = mBullets.erase(bulletIt);
        }else{
            ++bulletIt;
        }
    }

    //边界限制
    sf::Vector2f pos = mPlayer->getPosition();

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

    mPlayer->setPosition(pos);
}

void World::draw(){
    mWindow.clear(sf::Color::Black);

    mPlayer->draw(mWindow);

    for(auto& enemy : mEnemies){
        enemy->draw(mWindow);
    }

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
    sf::Vector2f playerPos = mPlayer->getPosition();
    bullet.setPosition(playerPos.x + 62.f, playerPos.y);

    mBullets.push_back(bullet);
}

void World::spawnEnemy(){
    if(mSpawnClock.getElapsedTime().asSeconds() < SpawnCooldown){
        return;
    }

    mSpawnClock.restart();

    auto enemy = std::make_unique<Aircraft>(Aircraft::Type::Enemy, mTextures);

    float x = static_cast<float>(rand() % (800 - 66)) - 31.f;
    enemy->setPosition(sf::Vector2f(x, -128.f));

    mEnemies.push_back(std::move(enemy));
}