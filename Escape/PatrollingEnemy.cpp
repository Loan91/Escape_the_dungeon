#include "PatrollingEnemy.h"

PatrollingEnemy::PatrollingEnemy(float width, float height, Vector2f startPoint, Vector2f endPoint, float speed, const sf::Texture& texture) : Enemy(width, height, startPoint, speed), startPoint(startPoint), endPoint(endPoint), movingToEnd(true)
{
	sprite.setTexture(texture);
    sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);
    sprite.setPosition(startPoint);
}

void PatrollingEnemy::update(float deltaTime, const Map& map)
{
    Vector2f targetPoint = movingToEnd ? endPoint : startPoint;
    Vector2f direction = targetPoint - sprite.getPosition();

    float length = sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        direction = direction / length;
    }

    sprite.move(direction * speed * deltaTime);

    if (length < speed * deltaTime)
    {
        movingToEnd = !movingToEnd;
        sprite.setPosition(targetPoint);
    }
    Vector2f position = sprite.getPosition();
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + sprite.getGlobalBounds().width > 1920) position.x = 1920 - sprite.getGlobalBounds().width;
    if (position.y + sprite.getGlobalBounds().height > 1080) position.y = 1080 - sprite.getGlobalBounds().height;
    sprite.setPosition(position);
}
