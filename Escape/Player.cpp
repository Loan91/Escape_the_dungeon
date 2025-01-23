#include "Player.h"

Player::Player(float width, float height, Vector2f startPosition, float startSpeed) : speed(startSpeed), hasKey(false)
{
    shape3.setSize({ width, height });
    shape3.setPosition(startPosition);
    shape3.setFillColor(Color::Blue);
}

void Player::handleInput(float deltaTime, const Map& map)
{
    if (Keyboard::isKeyPressed(Keyboard::Z))
    {
        shape3.move(0.0f, -speed);
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        shape3.move(0.0f, speed);
    }
    if (Keyboard::isKeyPressed(Keyboard::Q))
    {
        shape3.move(-speed, 0.0f);
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        shape3.move(speed, 0.0f);
    }
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
    Vector2f position = shape3.getPosition();
    if (!handleCollisions(map))
    {
        if (position.x < 0) position.x = 0;
        if (position.y < 0) position.y = 0;
        if (position.x + shape3.getSize().x > 1920) position.x = 1920 - shape3.getSize().x;
        if (position.y + shape3.getSize().y > 1080) position.y = 1080 - shape3.getSize().y;
        shape3.setPosition(position);
    }
    else
    {
        shape3.setPosition(position);
    }
   
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(shape3);
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

Vector2f Player::getPosition() const
{
    return shape3.getPosition();
}

FloatRect Player::getBounds() const
{
    return shape3.getGlobalBounds();
}
