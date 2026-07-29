#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity{
    public:
        explicit Entity(sf::Vector2f position);
        virtual ~Entity() = default;

        void update(sf::Time dt);
        void draw(sf::RenderWindow& window) const;

        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float vx, float vy);
        sf::Vector2f getVelocity() const;

        void move(sf::Vector2f offset);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition() const;

        sf::FloatRect getBoundingRect() const;

    protected:
        virtual void updateCurrent(sf::Time dt) = 0;
        sf::Sprite mSprite;

    private:
        sf::Vector2f mVelocity;

};

#endif //ENTITY_HPP