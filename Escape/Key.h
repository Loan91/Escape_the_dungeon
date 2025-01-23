#pragma once
#include "Interactable.h"
#include "includes.h"

class Key : public Interactable
{
private:
    sf::RectangleShape shape;
    bool isActive;

public:
    Key(sf::Vector2f size, sf::Vector2f position);
    void interact(Player& player) override;
    void draw(sf::RenderWindow& window);
    bool isCollidingWithPlayer(const Player& player) const;
    bool getIsActive() const;
};