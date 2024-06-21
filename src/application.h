#pragma once

#include <SDL_image.h>
#include <SDL_mixer.h>
#include <unordered_map>
#include <memory>
#include <array>
#include "assets.h"
#include "clock.h"
#include "mouse.h"
#include "input.h"
#include "boxTemplate.h"
#include "font.h"
#include "drawable.h"

using std::unordered_map;
using std::string;
using std::vector;
using std::array;
using std::shared_ptr;
using std::unique_ptr;
using std::static_pointer_cast;
using std::dynamic_pointer_cast;

namespace engix
{
    class Application
    {
    public:
        Application();
        ~Application();

        void loadAssets();

        void loop();

        void update();
        void render();
    private:
        Input currentInput;
        Input prevInput;

        Camera camera;

        Clock delta;
        Window window;
        Mouse mouse;

        std::vector<std::shared_ptr<Drawable>> drawables;

        unordered_map<string, shared_ptr<Texture>> textures;
        unordered_map<string, shared_ptr<BoxTemplate>> templates;
        unordered_map<string, shared_ptr<Font>> fonts;
    };
}