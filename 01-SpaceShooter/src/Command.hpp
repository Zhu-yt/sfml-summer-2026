#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <SFML/System/Time.hpp>
#include <functional>

class Entity;

struct Command{
    std::function<void(Entity&, sf::Time)> action;
    unsigned int category = 0;
};

#endif //COMMAND_HPP