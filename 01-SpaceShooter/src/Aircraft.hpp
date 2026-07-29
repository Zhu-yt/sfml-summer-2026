#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

class Aircraft : public Entity{
    public:
        enum class Type{
            Player,
            Enemy
        };

        explicit Aircraft(Type type, const ResourceHolder<sf::Texture, Textures::ID>& Textures);

        void updateCurrent(sf::Time dt) override;

    private:
        Type mType;
};

#endif //AIRCRAFT_HPP