#include "application.h"

using namespace engix;

engix::Application::Application() 
: window("Burgers :O", 1280, 720), currentInput(&prevInput)
{
    loadAssets();

    mouse = Mouse(textures["cursor"]);

    drawables.push_back(std::make_shared<Drawable>(textures["guy"]));
    drawables.back()->position({20, 39});
}

engix::Application::~Application()
{
}

void engix::Application::loadAssets()
{
    fonts["default"] = std::make_shared<Font>(assets::FONTS_PATH + "pixix");

    textures["cursor"] = std::make_shared<Texture>(assets::TEXTURES_PATH + "cursor.png");
    textures["guy"] = std::make_shared<Texture>(assets::TEXTURES_PATH + "guy.png");
}

void engix::Application::loop()
{
    while (currentInput.isRunning)
    {
        currentInput.update();
        update();
        render();
    }
}

void engix::Application::update()
{
    delta.restart();

    mouse.enable(currentInput.cursor.isShown);

    if (mouse.enable())
        mouse.update(currentInput);

    std::cout << currentInput.cursor.scroll << '\n';
    drawables.back()->scale(std::max(currentInput.cursor.scroll / 10.0, 0.1));
    auto rotation = drawables.back()->rotation();
    rotation.setDegs(rotation.degs() + delta.millis() / 10);
    drawables.back()->rotation(rotation);

    static auto time = 0.0l;
    time += delta.millis() * 0.1;

    constexpr auto d = 10;
    camera.position({std::sin(time) * d, std::cos(time) * d});
}

void engix::Application::render()
{
    window.fill({"222222"});

    //Render everything here

    for (const auto& drawable : drawables)
    {
        drawable->render(camera);
    }

    //Interface
    if (mouse.enable())
        mouse.render();
        
    window.update();
}