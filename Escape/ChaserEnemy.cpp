#include "ChaserEnemy.h"

ChaserEnemy::ChaserEnemy(float width, float height, Vector2f startPosition, float startSpeed, Player& target, const sf::Texture& texture) : Enemy(width, height, startPosition, startSpeed), target(target)
{
    sprite.setTexture(texture);
    sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);
    sprite.setPosition(startPosition);
}

void ChaserEnemy::update(float deltaTime, const Map& map)
{
    Vector2f direction = target.getPosition() - position;
    float magnitude = sqrt(direction.x * direction.x + direction.y * direction.y);

    if (magnitude > 0)
    {
        direction /= magnitude;
    }

    Vector2f newPosition = position + direction * speed * deltaTime;

    if (!map.checkCollision(sf::FloatRect(newPosition, sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height))))
    {
        position = newPosition;
    }
    else
    {
        Vector2f lateralDirection = { direction.y, -direction.x };
        Vector2f lateralPosition = position + lateralDirection * speed * deltaTime;

        if (!map.checkCollision(sf::FloatRect(lateralPosition, sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height))))
        {
            position = lateralPosition;
        }
        else
        {
            lateralDirection = { -direction.y, direction.x };
            lateralPosition = position + lateralDirection * speed * deltaTime;

            if (!map.checkCollision(sf::FloatRect(lateralPosition, sf::Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height))))
            {
                position = lateralPosition;
            }
        }
    }
    sprite.setPosition(position);
}

