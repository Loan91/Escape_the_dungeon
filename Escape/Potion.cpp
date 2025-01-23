#include "Potion.h"

Potion::Potion(float radius, sf::Vector2f position, float speedIncrease)
    : isActive(true), speedIncrease(speedIncrease)
{
    shape4.setRadius(radius);
    shape4.setPosition(position);
    shape4.setFillColor(sf::Color::Green);
    shape4.setOrigin(radius, radius);
}

void Potion::interact(Player& player)
{
    if (isActive)
    {
        player.setSpeed(player.getSpeed() + speedIncrease);
        isActive = false;

        shape4.setPosition({ std::rand() % 1800 + 50.0f, std::rand() % 1000 + 50.0f });
        isActive = true;
    }
}

void Potion::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(shape4);
    }
}

bool Potion::isCollidingWithPlayer(const Player& player) const
{
    return isActive && shape4.getGlobalBounds().intersects(player.getBounds());
}

bool Potion::getIsActive() const
{
    return isActive;
}
