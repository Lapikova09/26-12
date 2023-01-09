#pragma once
#include <SFML/Graphics.hpp>
#include "Header.h"
bool pointInRect(sf::RectangleShape bat, sf::Vector2f point) {
    return bat.getPosition().x <= point.x &&
        point.x <= bat.getPosition().x + BAT_SIZE.x &&
        bat.getPosition().y <= point.y &&
        point.y <= bat.getPosition().y + BAT_SIZE.y;
}

