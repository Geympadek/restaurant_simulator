#include "object.h"

engix::Object::Object(std::shared_ptr<Texture> texture)
: Drawable(std::move(texture))
{
    _width /= 4;
}

engix::Object::Object(std::shared_ptr<Texture> texture, int width, int height)
: Drawable(std::move(texture), width, height)
{
}

void engix::Object::render(const Camera &cam) const
{
    Drawable::renderClip(cam, Rect(static_cast<int>(_direction) * _width, 0, _width, _height));
#ifdef DISPLAY_COLLIDERS
    _collider.render(_position, _scale, Color::BLUE, cam);
#endif
}

void engix::Object::collide(Object &a, Object &b)
{
    auto arect = a._collider.toRect(a._position, a._scale);
    auto brect = b._collider.toRect(b._position, b._scale);

    auto intersection = Rect::intersection(arect, brect);
    if (!intersection)
    {
        return;
    }
    std::cout << "intersection!\n";

    int moveableCount = 0;
    if (a._moveable) moveableCount++; 
    if (b._moveable) moveableCount++;

    if (intersection.width < intersection.height)
    {
        auto movement = std::max(intersection.width, 1);
        auto sign = arect.start.x < brect.start.x ? 1 : -1;
        
        if (a._moveable)
            a._position.x -= movement * sign;
        if (b._moveable)
            b._position.x += movement * sign;
    } else
    {
        auto movement = std::max(intersection.height, 1);
        auto sign = arect.start.y < brect.start.y ? 1 : -1;
        
        if (a._moveable)
            a._position.y -= movement * sign;
        if (b._moveable)
            b._position.y += movement * sign;
    }
}