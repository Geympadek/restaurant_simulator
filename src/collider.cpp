#include "collider.h"

bool engix::Collider::checkCollision(Vector2i apos, Collider a, Vector2i bpos, Collider b)
{
    a.shift(a.shift() + apos);
    b.shift(b.shift() + bpos);

    return Rect::checkIntersection(a.rect(), b.rect());
}
