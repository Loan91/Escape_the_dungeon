#pragma once
#include "Player.h"
#include "includes.h"

class Interactable
{
public:
    virtual void interact(Player& player) = 0;
};