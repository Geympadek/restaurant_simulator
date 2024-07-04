#pragma once

#include "object.h"
#include "animation.h"
#include "pack.h"

namespace engix
{
    class Character : public Object
    {
    public:
        Character(Pack& pack);
        virtual void render(const Camera& camera) const override;
        virtual void update(Input& input) override;
    protected:
        void renderAnim(const Camera& cam) const;
        void renderAnimClip(const Camera& cam, Rect clip) const;
    protected:
        Pack& _pack;
        std::shared_ptr<Animation> _activeAnimation;
        Clock _animationTimer;
    };
}