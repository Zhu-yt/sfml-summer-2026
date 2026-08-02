#include "Entity.hpp"

Entity::Entity(sf::Vector2f position):mVelocity(0.f, 0.f){
    mSprite.setPosition(position);
}

void Entity::update(sf::Time dt){
    updateCurrent(dt);
    mSprite.move(mVelocity * dt.asSeconds());
}

void Entity::draw(sf::RenderWindow& window) const{
    window.draw(mSprite);
}

void Entity::setVelocity(sf::Vector2f velocity){
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy){
    mVelocity = sf::Vector2f(vx, vy);
}

sf::Vector2f Entity::getVelocity() const{
    return mVelocity;
}

void Entity::move(sf::Vector2f offset){
    mSprite.move(offset);
}

void Entity::setPosition(sf::Vector2f position){
    mSprite.setPosition(position);
}

sf::Vector2f Entity::getPosition() const{
    return mSprite.getPosition();
}

sf::FloatRect Entity::getBoundingRect() const{
    return mSprite.getGlobalBounds();
}

unsigned int Entity::getCategory() const{
    return Category::None;
}