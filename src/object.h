#pragma once

#include "drawable.h"

namespace engix
{
    using Collider = Rect;
    class Object : public Drawable
    {
    public:
        Object() {}
        Object(std::shared_ptr<Texture> texture) : Drawable(std::move(texture)) {}
        Object(std::shared_ptr<Texture> texture, int width, int height) : Drawable(std::move(texture), width, height) {}
    public:
        Collider collider() const {return _collider;}
        void collider(Collider collider) {_collider = collider;}
    protected:
        Collider _collider;
    };
}