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
            sf::RectangleShape shape5;
            shape5.setSize({ 50.0f, 50.0f });
            shape5.setPosition(x * 50.0f, y * 50.0f);

            if (tile == '1')
            {
                shape5.setTexture(&wallTexture);
                walls.push_back(shape5);
            }
            else if (tile == 'D')
            {
                shape5.setTexture(&doorTexture);
                door = shape5;
            }
            else if (tile == '0')
            {
                shape5.setTexture(&floorTexture);
                floorTiles.push_back(shape5);
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
        {
            return true;
        }
    }
    return false;
}

void Map::unlockDoor()
{
    doorUnlocked = true;
}

bool Map::checkDoorCollision(const sf::FloatRect& bounds) const
{
    if (doorUnlocked)
    {
        return false;
    }
    return door.getGlobalBounds().intersects(bounds);
}

bool Map::isDoorUnlocked() const
{
    return doorUnlocked;
}

void Map::setOpenedDoorTexture(sf::Texture& texture)
{
    openedDoorTexture = texture;
}
