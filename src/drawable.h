#pragma once

#include "fixedDrawable.h"
#include "camera.h"
#include <memory>
#include "window.h"

namespace engix
{ 
    //Object that's rendered relative to the camera's position
    class Drawable : public FixedDrawable
    {
    public:
        Drawable() {};
        Drawable(std::shared_ptr<Texture> texture);
        Drawable(std::shared_ptr<Texture> texture, int width, int height);
        virtual ~Drawable() {}

        virtual void render(const Camera& camera) const;
    private:
        //Hoping that this function will not be accessable
        virtual void render() const override {}
    public:
        int width() const {return _width;}
        int height() const {return _height;}
    protected:
        int _width;
        int _height;
    };
}