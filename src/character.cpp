#include "character.h"

engix::Character::Character(Pack &pack)
: Object(pack.textures["stand"]), _pack(pack)
{
    _activeAnimation = pack.animations["walk"];
    _animationTimer.start();
}

void engix::Character::render(const Camera &camera) const
{
    if (_activeAnimation == nullptr)
    {
        Object::render(camera);
    }
    else
    {
        renderAnimClip(camera, Rect(static_cast<int>(_direction) * _width, 0, _width, _height));
    }
}

void engix::Character::update(Input &input)
{
    Object::update(input);

    if (_activeAnimation != nullptr)
    {
        if (_animationTimer.millis() > _activeAnimation->duration())
        {
            _animationTimer.restart();
        }
    }
}

void engix::Character::renderAnim(const Camera &cam) const
{
    Vector2d pos;
    double scale;
    renderInfo(cam, pos, scale);
    
    _activeAnimation->render(_animationTimer.millis(), pos, scale, _rotation, _center, _flip);
}

void engix::Character::renderAnimClip(const Camera &cam, Rect clip) const
{
    Vector2d pos;
    double scale;
    renderInfo(cam, pos, scale);

    _activeAnimation->render(_animationTimer.millis(), pos, clip, scale, _rotation, _center, _flip);
}
