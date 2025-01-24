#pragma once
#include "Player.h"
#include "includes.h"

class Interactable
{
public:
    virtual void interact(Player& player) = 0;
    virtual void update(float deltaTime) = 0;
};