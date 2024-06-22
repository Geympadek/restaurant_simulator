#pragma once

#include "vector2.h"
#include "rect.h"

namespace engix
{
    class Collider
    {
    public:
        Collider() {}
        Collider(Vector2i shift, int width, int height) : _rect(shift, width, height) {}
        Collider(Rect rect) : _rect(rect) {}
    
        static bool checkCollision(Vector2i apos, Collider a, Vector2i bpos, Collider b);
    public:
        Vector2i shift() const {return _rect.start;}
        void shift(Vector2i shift) {_rect.start = shift;}

        int width() const {return _rect.width;}
        void width(int width) {_rect.width = width;}
        int height() const {return _rect.height;}
        void height(int height) {_rect.height = height;}

        Rect rect() const {return _rect;}
        void rect(Rect rect) {_rect = rect;}
    protected:
        Rect _rect;
    };
}