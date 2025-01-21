#pragma once
#include "includes.h"

class Map
{
private:
    std::vector<sf::RectangleShape> walls;
    std::vector<sf::RectangleShape> floorTiles;
    sf::RectangleShape door;
    bool doorUnlocked;

    sf::Texture wallTexture;
    sf::Texture floorTexture;
    sf::Texture doorTexture;
    sf::Texture openedDoorTexture;

public:
    Map();

    bool loadFromFile(const std::string& filePath);

    void draw(sf::RenderWindow& window);

    bool checkCollision(const sf::FloatRect& bounds) const;

    bool checkDoorCollision(const sf::FloatRect& bounds) const;

    void unlockDoor() { doorUnlocked = true; }

    bool isDoorUnlocked() const { return doorUnlocked; }

    void setOpenedDoorTexture(sf::Texture& texture) { openedDoorTexture = texture; }
};