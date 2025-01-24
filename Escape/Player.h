#pragma once
#include "includes.h"
#include "Entity.h"

class Player : public Entity
{
private:
    float speed;
    sf::Texture texture;
    sf::Sprite sprite;
    bool hasKey;
    sf::Vector2f movement;
public:
    Player(float width, float height, Vector2f startPosition, float startSpeed, const sf::Texture& texture);
    void handleInput(float deltaTime, const Map& map);
    bool handleCollisions(const Map& map);
    void update(float deltaTime, const Map& map) override;
    void draw(sf::RenderWindow& window) override;

    float getSpeed() const;
    void setSpeed(float newSpeed);
    void setHasKey(bool state);
    bool getHasKey() const;
    Vector2f getPosition() const;
    FloatRect getBounds() const;
    void increaseSpeed(float amount);
};