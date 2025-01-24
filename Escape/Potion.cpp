#include "Potion.h"

Potion::Potion(sf::Texture& texture, sf::Vector2f position, float speedIncrease, sf::Vector2f size) : isActive(true), speedIncrease(speedIncrease), texture(&texture), floatAmplitude(10.0f), floatSpeed(2.0f), baseY(position.y)
{
    sprite.setTexture(*this->texture);
    sprite.setPosition(position);
    sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
}

void Potion::interact(Player& player)
{
    if (isActive)
    {
        player.setSpeed(player.getSpeed() + speedIncrease);
        isActive = false;

        sf::Vector2f newPosition = { std::rand() % 1800 + 50.0f, std::rand() % 1000 + 50.0f };
        sprite.setPosition(newPosition);
        baseY = newPosition.y;
        isActive = true;
    }
}

void Potion::update(float deltaTime)
{
    if (isActive)
    {
        float elapsed = animationClock.getElapsedTime().asSeconds();
        float offsetY = floatAmplitude * std::sin(floatSpeed * elapsed);
        sprite.setPosition(sprite.getPosition().x, baseY + offsetY);
    }
}

void Potion::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(sprite);
    }
}

bool Potion::isCollidingWithPlayer(const Player& player) const
{
    return isActive && sprite.getGlobalBounds().intersects(player.getBounds());
}

bool Potion::getIsActive() const
{
    return isActive;
}
