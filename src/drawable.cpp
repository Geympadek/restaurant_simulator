#include "drawable.h"
#include <atomic>

static std::atomic<size_t> idCount = 1;

engix::Drawable::Drawable(std::shared_ptr<Texture> texture) 
: FixedDrawable(std::move(texture)), _width(_texture->width()), _height(_texture->height()), _id(idCount++)
{
}

engix::Drawable::Drawable(std::shared_ptr<Texture> texture, int width, int height)
: FixedDrawable(std::move(texture)), _width(width), _height(height), _id(idCount++)
{
}

engix::Drawable::Drawable(const Drawable &a) : FixedDrawable(a), _width(a._width), _height(a._height), _id(idCount++)
{

}

void engix::Drawable::render(const Camera &camera) const
{
    renderClip(camera, Rect(0, 0, _texture->width(), _texture->height()));
}

void engix::Drawable::renderClip(const Camera& camera, Rect clip) const
{
    Vector2i centerOfScreen(gScreen.width / 2, gScreen.height / 2);

    auto screenPos = (_position - camera.position()) * camera.scale() + centerOfScreen;
    auto screenScale = _scale * camera.scale();
    _texture->render(screenPos, clip, screenScale, _rotation, _center, _flip, _scaling);
}
