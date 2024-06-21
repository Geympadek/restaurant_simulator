#include "drawable.h"

engix::Drawable::Drawable(std::shared_ptr<Texture> texture) 
: FixedDrawable(texture)
{
}

void engix::Drawable::render(const Camera &camera) const
{
    auto screenPos = _position - camera.position();
    auto screenScale = _scale * camera.scale();
    _texture->render(screenPos, screenScale, _rotation, screenPos, _flip, _scaling);
}