#include "Potion.h"

Potion::Potion(float radius, sf::Vector2f position, float speedIncrease)
    : isActive(true), speedIncrease(speedIncrease)
{
    shape.setRadius(radius);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(radius, radius);
}

void Potion::interact(Player& player)
{
    if (isActive)
    {
        player.setSpeed(player.getSpeed() + speedIncrease);
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