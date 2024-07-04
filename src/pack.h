#pragma once

#include <unordered_map>
#include <memory>
#include "texture.h"
#include "animation.h"
#include "font.h"
#include "boxTemplate.h"

namespace engix
{
    struct Pack
    {
        mutable std::unordered_map<C_Str<char>, std::shared_ptr<Texture>> textures;
        mutable std::unordered_map<C_Str<char>, std::shared_ptr<Animation>> animations;
        mutable std::unordered_map<C_Str<char>, std::shared_ptr<Font>> fonts;
        mutable std::unordered_map<C_Str<char>, std::shared_ptr<BoxTemplate>> templates;
    };
}
