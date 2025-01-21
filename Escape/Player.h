#pragma once
#include "includes.h"
#include "Entity.h"

class Player : public Entity
{
private:
    float speed;
    RectangleShape shape;
    bool hasKey;
    sf::Vector2f movement;
public:
    Player(float width, float height, Vector2f startPosition, float startSpeed);
    void handleInput(float deltaTime, const Map& map);
    void handleCollisions(const Map& map);
    void update(float deltaTime, const Map& map) override;
    void draw(sf::RenderWindow& window) override;

    float getSpeed() const { return speed; }
    void setSpeed(float newSpeed) { speed = newSpeed; }
    bool getHasKey() const { return hasKey; }
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