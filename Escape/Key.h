#pragma once
#include "Interactable.h"
#include "includes.h"

class Key : public Interactable
{
private:
    sf::Sprite sprite;
    sf::Texture* texture;
    bool isActive;

    float floatAmplitude;
    float floatSpeed;
    float baseY;
    Clock animationClock;
public:
    Key(sf::Texture& texture, sf::Vector2f position, sf::Vector2f size);
    void interact(Player& player) override;
    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window);
    bool isCollidingWithPlayer(const Player& player) const;
    bool getIsActive() const;
};