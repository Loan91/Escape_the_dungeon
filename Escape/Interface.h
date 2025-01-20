#pragma once
#include "Player.h"

class Interface
{
public:
    virtual ~Interface() = default;
    virtual void interact(Player& player) = 0;
};