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
    Vector2d screenPos;
    double screenScale;
    renderInfo(camera, screenPos, screenScale);
    _texture->render(screenPos, clip, screenScale, _rotation, _center, _flip, _scaling);
}

void engix::Drawable::renderInfo(const Camera& cam, Vector2d &renderPos, double &scale) const
{
    Vector2d centerOfScreen(gScreen.width / 2, gScreen.height / 2);
    renderPos = (_position - cam.position()) * cam.scale() + centerOfScreen;
    scale = _scale * cam.scale();
}
