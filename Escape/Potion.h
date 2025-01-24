#pragma once
#include "Interactable.h"
#include "includes.h"

class Potion : public Interactable
{
private:
    sf::Sprite sprite;
    sf::Texture* texture;
    bool isActive;
    float speedIncrease;

public:
    Potion(sf::Texture& texture, sf::Vector2f position, float speedIncrease, sf::Vector2f size);
    void interact(Player& player) override;
    void draw(sf::RenderWindow& window);
    bool isCollidingWithPlayer(const Player& player) const;
    bool getIsActive() const;
};