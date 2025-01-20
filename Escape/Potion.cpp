#include "Potion.h"

Potion::Potion(float radius, sf::Vector2f position) : isActive(true)
{
    shape.setRadius(radius);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Green);
}

void Potion::interact(Player& player)
{
    if (isActive)
    {
        player.increaseSpeed(1.0f);
        isActive = false;
    }
}

void Potion::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(shape);
    }
}

bool Potion::isCollidingWithPlayer(const Player& player) const
{
    return isActive && shape.getGlobalBounds().intersects(player.getBounds());
}