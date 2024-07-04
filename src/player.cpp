#include "player.h"

engix::Player::Player(Pack &pack)
: Character(pack)
{
}

void engix::Player::update(Input &input)
{
    Character::update(input);

    Vector2d movement;
    if (input.inputs[Control::LEFT])
    {
        movement.x--;
        _direction = Direction::LEFT;
    }
    if (input.inputs[Control::RIGHT])
    {
        movement.x++;
        _direction = Direction::RIGHT;
    }
    if (input.inputs[Control::UP])
    {
        movement.y--;
        _direction = Direction::UP;
    }
    if (input.inputs[Control::DOWN])
    {
        movement.y++;
        _direction = Direction::DOWN;
    }
    _position += Vector2d::normalize(movement) * _movementSpeed;

    if (movement != Vector2d())
        _activeAnimation = _pack.animations["walk"];
    else
        _activeAnimation = nullptr;
}
