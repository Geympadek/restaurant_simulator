#include "collider.h"
#include "window.h"

using namespace engix;

void engix::Collider::render(Vector2i pos, double scale, Color color, const Camera &cam) const noexcept
{
    Vector2i centerOfScreen(gScreen.width / 2, gScreen.height / 2);

    auto screenPos = (pos + _rect.start - cam.position()) * cam.scale() + centerOfScreen;
    auto screenScale = scale * cam.scale();
    Rect rect(screenPos, static_cast<int>(_rect.width * screenScale), static_cast<int>(_rect.height * screenScale));
    rect.render(color);
}