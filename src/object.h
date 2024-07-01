#pragma once

#include "drawable.h"
#include "collider.h"

#define DISPLAY_COLLIDERS

namespace engix
{
    enum class Direction {DOWN = 0, UP = 1, LEFT = 2, RIGHT = 3 };
    
    class Object : public Drawable
    {
    public:
        Object() {}
        Object(std::shared_ptr<Texture> texture);
        Object(std::shared_ptr<Texture> texture, int width, int height);

        virtual void render(const Camera& cam) const override;

        static bool checkCollision(const Object& a, const Object& b) {return Collider::checkCollision(a._position, a._scale, a._collider, b._position, b._scale, b._collider);}
        static void collide(Object& a, Object& b);
    public:
        Collider collider() const {return _collider;}
        void collider(Collider collider) {_collider = collider;}

        bool moveable() const {return _moveable;}
        void moveable(bool moveable) {_moveable = moveable;}

        Direction direction() const {return _direction;}
        void direction(Direction dir) {_direction = dir;}
    protected:
        Collider _collider;
        bool _moveable = true;

        Direction _direction = Direction::DOWN;
    };
}