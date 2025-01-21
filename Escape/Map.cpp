#include "Map.h"

Map::Map() : doorUnlocked(false)
{
    if (!wallTexture.loadFromFile("assets/wall.jpg"))
        throw std::runtime_error("Erreur lors du chargement de la texture des murs.");
    if (!floorTexture.loadFromFile("assets/floor.jpg"))
        throw std::runtime_error("Erreur lors du chargement de la texture du sol.");
    if (!doorTexture.loadFromFile("assets/door.png"))
        throw std::runtime_error("Erreur lors du chargement de la texture de la porte.");
}

bool Map::loadFromFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    if (!file.is_open())
        return false;

    std::string line;
    int y = 0;

    while (std::getline(file, line))
    {
        for (size_t x = 0; x < line.size(); ++x)
        {
            char tile = line[x];
            sf::RectangleShape shape;
            shape.setSize({ 50.0f, 50.0f });
            shape.setPosition(x * 50.0f, y * 50.0f);

            if (tile == '1')
            {
                shape.setTexture(&wallTexture);
                walls.push_back(shape);
            }
            else if (tile == 'D')
            {
                shape.setTexture(&doorTexture);
                door = shape;
            }
            else if (tile == '0')
            {
                shape.setTexture(&floorTexture);
                floorTiles.push_back(shape);
            }
        }
        ++y;
    }
    return true;
}

void Map::draw(sf::RenderWindow& window)
{
    for (const auto& floorTile : floorTiles)
    {
        window.draw(floorTile);
    }

    for (const auto& wall : walls)
    {
        window.draw(wall);
    }

    if (!doorUnlocked)
    {
        window.draw(door);
    }
    else
    {
        door.setTexture(&openedDoorTexture);
        window.draw(door);
    }
}

bool Map::checkCollision(const sf::FloatRect& bounds) const
{
    for (const auto& wall : walls)
    {
        if (wall.getGlobalBounds().intersects(bounds))
            return true;
    }
    return false;
}

bool Map::checkDoorCollision(const sf::FloatRect& bounds) const
{
    return door.getGlobalBounds().intersects(bounds);
}