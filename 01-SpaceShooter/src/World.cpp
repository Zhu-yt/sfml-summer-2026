#include "World.hpp"
#include <iostream>

const float World::PlayerSpeed = 300.f;
const float World::ShootCooldown = 0.2f;
const float World::SpawnCooldown = 2.0f;

World::World(sf::RenderWindow& window)
:mWindow(window)
,mIsShooting(false)
,mScore(0)
,mMaxHP(100)
,mPlayerHP(100)
,mGameOver(false){
    loadTextures();
    buildScene();

    mFont.loadFromFile("assets/fonts/Sansation.ttf");
    mScoreText.setFont(mFont);
    mScoreText.setPosition(10.f, 10.f);
    mScoreText.setCharacterSize(20);
    mScoreText.setColor(sf::Color::White);
    mScoreText.setString("Score: 0");

    mHPBarBackground.setSize(sf::Vector2f(200.f, 20.f));
    mHPBarBackground.setFillColor(sf::Color(80, 80, 80));
    mHPBarBackground.setPosition(10.f, 40.f);

    mHPBar.setSize(sf::Vector2f(200.f, 20.f));
    mHPBar.setFillColor(sf::Color::Green);
    mHPBar.setPosition(10.f, 40.f);

}

void World::loadTextures(){
    mTextures.load(Textures::Player, "assets/textures/player.png");
}

void World::buildScene(){
    mPlayer = std::make_unique<Aircraft>(Aircraft::Type::Player, mTextures);
    mPlayer->setPosition(sf::Vector2f(336.f, 472.f));
}

CommandQueue& World::getCommandQueue(){
    return mCommandQueue;
}

void World::update(sf::Time dt){
    if(mGameOver){
        return;
    }

    while(!mCommandQueue.isEmpty()){
        onCommand(mCommandQueue.pop(), dt);
    }
    
    //连续移动
    mPlayer->update(dt);

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

    if(mIsShooting){
        shoot();
    }

    //子弹移动
    float delta = dt.asSeconds();
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

    //生成敌人和更新
    spawnEnemy();
    for(auto& enemy : mEnemies){
        enemy->update(dt);
    }

    //碰撞检测
    for(auto bulletIt = mBullets.begin(); bulletIt != mBullets.end(); ){
        bool hit = false;

        for(auto enemyIt = mEnemies.begin(); enemyIt != mEnemies.end(); ){
            if(bulletIt->getGlobalBounds().intersects((*enemyIt)->getBoundingRect())){
                enemyIt = mEnemies.erase(enemyIt);
                hit = true;
                mScore += 100;
                mScoreText.setString("Score: " + std::to_string(mScore));

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

    for(auto enemyIt = mEnemies.begin(); enemyIt != mEnemies.end(); ){
        if((*enemyIt)->getBoundingRect().intersects(mPlayer->getBoundingRect())){
            mPlayerHP -= 20;
            enemyIt = mEnemies.erase(enemyIt);

            if(mPlayerHP <= 0){
                mPlayerHP = 0;
                mGameOver = true;
            }
        }else{
            ++enemyIt;
        }
    }
    
    //敌人消失
    mEnemies.erase(
        std::remove_if(mEnemies.begin(), mEnemies.end(), 
            [](const std::unique_ptr<Aircraft>& e){
                return e->getPosition().y > 600.f + 79.f;
            }),
        mEnemies.end()
    );
}

void World::onCommand(const Command& command, sf::Time dt){
    if(command.category & mPlayer->getCategory()){
        command.action(*mPlayer, dt);
    }
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

    float hpPercent = static_cast<float>(mPlayerHP)/(mMaxHP);
    mHPBar.setSize(sf::Vector2f(200.f * hpPercent, 20.f));

    if(hpPercent < 0.3f){
        mHPBar.setFillColor(sf::Color::Red);
    }else{
        mHPBar.setFillColor(sf::Color::Green);
    }

    mWindow.draw(mHPBarBackground);
    mWindow.draw(mHPBar);
    mWindow.draw(mScoreText);

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