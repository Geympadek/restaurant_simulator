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

        Drawable(const Drawable& a);
        Drawable(Drawable&&) = default;

        virtual void render(const Camera& camera) const;
    protected:
        void renderClip(const Camera& camera, Rect clip) const;
    private:
        //Hoping that this function will not be accessable
        virtual void render() const override {}
    public:
        size_t id() const noexcept {return _id;}

        virtual int width() const noexcept {return _width;}
        virtual int height() const noexcept {return _height;}
    protected:
        size_t _id = 0;

        int _width;
        int _height;
    };
}