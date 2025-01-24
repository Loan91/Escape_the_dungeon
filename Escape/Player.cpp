#include "Player.h"

Player::Player(float width, float height, sf::Vector2f startPosition, float startSpeed, const sf::Texture& texture) : speed(startSpeed), hasKey(false)
{
    sprite.setTexture(texture);
    sprite.setPosition(startPosition);
    sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);
}

void Player::handleInput(float deltaTime, const Map& map)
{
    sf::Vector2f movement(0.0f, 0.0f);

    if (Keyboard::isKeyPressed(Keyboard::Z))
        movement.y -= speed;
    if (Keyboard::isKeyPressed(Keyboard::S))
        movement.y += speed;
    if (Keyboard::isKeyPressed(Keyboard::Q))
        movement.x -= speed;
    if (Keyboard::isKeyPressed(Keyboard::D))
        movement.x += speed;

    sf::FloatRect newBounds = sprite.getGlobalBounds();
    newBounds.left += movement.x;
    newBounds.top += movement.y;

    if (!map.checkCollision(newBounds))
        sprite.move(movement);
}

void Player::increaseSpeed(float amount)
{
    speed += amount;
}

bool Player::handleCollisions(const Map& map)
{
    if (map.checkCollision(getBounds()))
    {
        return true;
    }

    if (map.checkDoorCollision(getBounds()))
    {
        return true;
    }
    return false;
}

void Player::update(float deltaTime, const Map& map)
{
    handleInput(deltaTime, map);
    sf::Vector2f position = sprite.getPosition();

    if (!handleCollisions(map))
    {
        if (position.x < 0) position.x = 0;
        if (position.y < 0) position.y = 0;
        if (position.x + sprite.getGlobalBounds().width > 1920)
            position.x = 1920 - sprite.getGlobalBounds().width;
        if (position.y + sprite.getGlobalBounds().height > 1080)
            position.y = 1080 - sprite.getGlobalBounds().height;

        sprite.setPosition(position);
    }
    else
    {
        sprite.setPosition(position);
    }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

float Player::getSpeed() const
{
    return speed;
}

void Player::setSpeed(float newSpeed)
{
    speed = newSpeed;
}

bool Player::getHasKey() const
{
    return hasKey;
}

void Player::setHasKey(bool state)
{
    hasKey = state;
}

Vector2f Player::getPosition() const
{
    return sprite.getPosition();
}

FloatRect Player::getBounds() const
{
    return sprite.getGlobalBounds();
}
