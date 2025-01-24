#include "Key.h"

Key::Key(sf::Texture& texture, sf::Vector2f position, sf::Vector2f size) : isActive(true), texture(&texture), floatAmplitude(8.0f), floatSpeed(1.5f), baseY(position.y) 
{
    sprite.setTexture(*this->texture);
    sprite.setPosition(position);
    sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
}

void Key::interact(Player& player)
{
    if (isActive)
    {
        std::cout << "Key collected!" << std::endl;
        player.setHasKey(true);
        isActive = false;
    }
}

void Key::update(float deltaTime)
{
    if (isActive)
    {
        float elapsed = animationClock.getElapsedTime().asSeconds();
        float offsetY = floatAmplitude * std::sin(floatSpeed * elapsed);
        sprite.setPosition(sprite.getPosition().x, baseY + offsetY);
    }
}

void Key::draw(sf::RenderWindow& window)
{
    if (isActive)
    {
        window.draw(sprite);
    }
}

bool Key::isCollidingWithPlayer(const Player& player) const
{
    return isActive && sprite.getGlobalBounds().intersects(player.getBounds());
}

bool Key::getIsActive() const
{
    return isActive;
}
