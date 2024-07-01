#pragma once

#include "object.h"

namespace engix
{
    class Character : public Object
    {
    public:
        Character() {}
        Character(shared_ptr<Texture> texture);
        Character(shared_ptr<Texture> texture, int width, int height);

        virtual void update(Input& input) override;
    protected:
    };
}