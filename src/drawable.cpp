#include "drawable.h"

engix::Drawable::Drawable(std::shared_ptr<Texture> texture) 
: FixedDrawable(std::move(texture)), _width(_texture->width()), _height(_texture->height())
{
}

engix::Drawable::Drawable(std::shared_ptr<Texture> texture, int width, int height)
: FixedDrawable(std::move(texture)), _width(width), _height(height)
{
}

void engix::Drawable::render(const Camera &camera) const
{
    Vector2i centerOfScreen(gScreen.width / 2, gScreen.height / 2);

    auto screenPos = (_position - camera.position()) * camera.scale() + centerOfScreen;
    auto screenScale = _scale * camera.scale();
    _texture->render(screenPos, screenScale, _rotation, _center, _flip, _scaling);
}