#pragma once

#include "character.h"

namespace engix
{
    class Player : public Character
    {
    public:
        Player(Pack& pack);
        virtual void update(Input& input) override;
    public:
        virtual double movementSpeed() const {return _movementSpeed;}
        virtual void movementSpeed(double movementSpeed) {_movementSpeed = movementSpeed;}
    protected:
        double _movementSpeed = 1.0;
    };
}