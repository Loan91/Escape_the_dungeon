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

    float getSpeed() const;
    void setSpeed(float newSpeed);
    bool getHasKey() const;
    Vector2f getPosition() const;
    FloatRect getBounds() const;
    void increaseSpeed(float amount);
};