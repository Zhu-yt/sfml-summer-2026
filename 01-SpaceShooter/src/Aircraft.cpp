#include "Aircraft.hpp"

Aircraft::Aircraft(Type type, const ResourceHolder<sf::Texture, Textures::ID>& textures)
:Entity(sf::Vector2f(0.f, 0.f))
,mType(type){
    switch (type){
    case Type::Player:
        mSprite.setTexture(textures.get(Textures::Player));
        break;
    
    case Type::Enemy:
        mSprite.setTexture(textures.get(Textures::Player));
        mSprite.setColor(sf::Color::Red);
        mSprite.setScale(1.f, -1.f);
        break;
    }
}

void Aircraft::updateCurrent(sf::Time dt){
    if(mType == Type::Enemy){
        setVelocity(0.f, 200.f);
    }
}