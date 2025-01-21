#pragma once
#include "includes.h"
#include "Entity.h"
#include "Map.h"

class Player : public Entity
{
private:
    float speed;
    RectangleShape shape;
    bool hasKey;
public:
    Player(float width, float height, Vector2f startPosition, float startSpeed);
    void handleInput(float deltaTime);
    void handleCollisions(const Map& map);
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window) override;
    void updateWithMap(float deltaTime, const Map& map);

    float getSpeed() const { return speed; }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    bool getHasKey() const { return hasKey; }
    void setHasKey(bool key) { hasKey = key; }
    Vector2f getPosition() const
    {
        return shape.getPosition();
    }
    FloatRect getBounds() const
    {
        return shape.getGlobalBounds();
    }
    void increaseSpeed(float amount);
};