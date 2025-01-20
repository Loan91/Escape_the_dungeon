#pragma once
#include "Interface.h"

class Potion : public Interface
{
private:
    sf::CircleShape shape;
    bool isActive;

public:
    Potion(float radius, sf::Vector2f position);
    void interact(Player& player) override;
    void draw(sf::RenderWindow& window);
    bool isCollidingWithPlayer(const Player& player) const;
    bool getIsActive() const { return isActive; }
};