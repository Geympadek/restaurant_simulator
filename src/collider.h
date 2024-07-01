#pragma once

#include "vector2.h"
#include "rect.h"
#include "color.h"
#include "camera.h"

namespace engix
{
    class Collider
    {
    public:
        constexpr Collider() noexcept {}
        constexpr Collider(int x, int y, int width, int height) noexcept : _rect(x, y, width, height) {}
        constexpr Collider(Vector2i shift, int width, int height) noexcept : _rect(shift, width, height) {}
        constexpr Collider(Rect rect) noexcept : _rect(rect) {}
    
        static constexpr bool checkCollision(Vector2i apos, double ascale, Collider a, Vector2i bpos, double bscale, Collider b)
        {return Rect::checkIntersection(a.toRect(apos, ascale), b.toRect(bpos, bscale));}
        static constexpr Rect intersection(Vector2i apos, double ascale, Collider a, Vector2i bpos, double bscale, Collider b) noexcept
        {return Rect::intersection(a.toRect(apos, ascale), b.toRect(bpos, bscale));}

        void render(Vector2i pos, double scale, Color color, const Camera& cam) const noexcept;
    public:
        constexpr Vector2i shift() const noexcept {return _rect.start;}
        constexpr void shift(Vector2i shift) noexcept {_rect.start = shift;}

        constexpr int width() const noexcept {return _rect.width;}
        constexpr void width(int width) noexcept {_rect.width = width;}
        constexpr int height() const noexcept {return _rect.height;}
        constexpr void height(int height) noexcept {_rect.height = height;}

        constexpr Rect toRect(Vector2i pos, double scale) const noexcept 
        {return {pos + _rect.start, static_cast<int>(scale * _rect.width), static_cast<int>(scale * _rect.height)};}
    protected:
        Rect _rect;
    };
}