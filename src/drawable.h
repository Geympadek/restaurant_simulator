#pragma once

#include "fixedDrawable.h"
#include "camera.h"
#include <memory>

namespace engix
{ 
    //Object that's rendered relative to the camera's position
    class Drawable : public FixedDrawable
    {
    public:
        Drawable() {};
        Drawable(std::shared_ptr<Texture> texture);
        virtual ~Drawable() {}

        virtual void render(const Camera& camera) const;
    private:
        //Hoping that this function will not be accessable
        virtual void render() const override {}
    };
}