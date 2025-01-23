#include "Key.h"

Key::Key(sf::Vector2f size, sf::Vector2f position) : isActive(true)
{
    shape2.setSize(size);
    shape2.setPosition(position);
    shape2.setFillColor(sf::Color::Yellow);
}

void Key::interact(Player& player)
{
    if (isActive)
    {
        std::cout << "Key collected!" << std::endl;
        isActive = false;

    }
}

void Key::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(shape2);
    }
}

bool Key::isCollidingWithPlayer(const Player& player) const
{
    return isActive && shape2.getGlobalBounds().intersects(player.getBounds());
}

bool Key::getIsActive() const
{
    return isActive;
}
