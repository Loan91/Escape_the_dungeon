#include "PatrollingEnemy.h"

PatrollingEnemy::PatrollingEnemy(float width, float height, Vector2f startPoint, Vector2f endPoint, float speed) : Enemy(width, height, startPoint, speed), startPoint(startPoint), endPoint(endPoint), movingToEnd(true)
{
	shape1.setPosition(startPoint);
}

void PatrollingEnemy::update(float deltaTime, const Map& map)
{
	Vector2f targetPoint = movingToEnd ? endPoint : startPoint;
	Vector2f direction = targetPoint - shape1.getPosition();

	float length = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length != 0)
	{
		direction = direction / length;
	}

	shape1.move(direction * speed * deltaTime);

	if (length < speed * deltaTime)
	{
		movingToEnd = !movingToEnd;
		shape1.setPosition(targetPoint);
	}

	Vector2f position = shape1.getPosition();
	if (position.x < 0) position.x = 0;
	if (position.y < 0) position.y = 0;
	if (position.x + shape1.getSize().x > 1920) position.x = 1920 - shape1.getSize().x;
	if (position.y + shape1.getSize().y > 1080) position.y = 1080 - shape1.getSize().y;
	shape1.setPosition(position);
}