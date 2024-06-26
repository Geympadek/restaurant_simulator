#pragma once

#include "vector2.h"

namespace engix
{
    class Camera
    {
    public:
        Camera();
        ~Camera();

        void update();
    public:
        double scale() const {return _scale;}
        void scale(double scale) {_scale = scale;}
        Vector2d position() const {return _position;}
        void position(Vector2d pos) {_position = pos;}
    private:
        double _scale = 1.0f;
        Vector2d _position;
    };
}