#include "PatrollingEnemy.h"

PatrollingEnemy::PatrollingEnemy(float width, float height, Vector2f startPoint, Vector2f endPoint, float speed) : Enemy(width, height, startPoint, speed), startPoint(startPoint), endPoint(endPoint), movingToEnd(true) 
{
    shape.setPosition(startPoint);
}

void PatrollingEnemy::update(float deltaTime, const Map& map)
{
	Vector2f targetPoint = movingToEnd ? endPoint : startPoint;
	Vector2f direction = targetPoint - shape.getPosition();

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction = direction / length;
	}

	shape.move(direction * speed * deltaTime);

	if (length < speed * deltaTime)
	{
		movingToEnd = !movingToEnd;
		shape.setPosition(targetPoint);
	}

	Vector2f position = shape.getPosition();
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + shape.getSize().x > 1920) position.x = 1920 - shape.getSize().x;
	if (position.y + shape.getSize().y > 1080) position.y = 1080 - shape.getSize().y;
	shape.setPosition(position);
}
