#include "rect.h"

void engix::Rect::render(Color color) const noexcept
{
    Rect rRect = *this;
    rRect.start *= static_cast<int>(roundPixelScale);
    rRect.width *= static_cast<int>(roundPixelScale);
    rRect.height *= static_cast<int>(roundPixelScale);
    
    Vector2i points[8];
    points[0] = rRect.start;
    points[1] = points[0] + Vector2i(rRect.width, 0);
    points[2] = points[1];
    points[3] = points[2] + Vector2i(0, rRect.height);
    points[4] = points[3];
    points[5] = points[0] + Vector2i(0, rRect.height);
    points[6] = points[5];
    points[7] = points[0];
    SDL_SetRenderDrawColor(gRenderer, color.red, color.green, color.blue, color.alpha);
    SDL_RenderDrawLines(gRenderer, reinterpret_cast<SDL_Point*>(&points), 8);
}