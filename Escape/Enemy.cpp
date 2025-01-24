#include "Enemy.h"

Enemy::Enemy(float width, float height, Vector2f startPosition, float startSpeed) : position(startPosition), speed(startSpeed)
{
    sprite.setPosition(startPosition);
}

void Enemy::setTexture(const sf::Texture& texture)
{
    this->texture = texture;
    sprite.setTexture(this->texture);
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

FloatRect Enemy::getBounds() const
{
    return sprite.getGlobalBounds();
}