#include "character.h"

engix::Character::Character(shared_ptr<Texture> texture) 
: Object(std::move(texture))
{
}

engix::Character::Character(shared_ptr<Texture> texture, int width, int height)
: Object(std::move(texture), width, height)
{
}

void engix::Character::update(Input &input)
{
    Object::update(input);
}
