#pragma once
#include "Interface.h"
#include "includes.h"

class Potion : public Interface
{
private:
    sf::CircleShape shape;
    bool isActive;
    float speedIncrease;

public:
    Potion(float radius, sf::Vector2f position, float speedIncrease);
    void interact(Player& player) override;
    void draw(sf::RenderWindow& window);
    bool isCollidingWithPlayer(const Player& player) const;
    bool getIsActive() const { return isActive; }
};