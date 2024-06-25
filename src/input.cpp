#include "input.h"
#include "window.h"
#include "encoding.h"
#include "assets.h"

using namespace engix;

static Clock cursorClock;
void Input::update()
{
    assert(prevInput != nullptr);
    if (!prevInput->isReading && isReading)
    {
        SDL_StartTextInput();
    }
    else if (prevInput->isReading && !isReading)
    {
        SDL_StopTextInput();
    }
    
    *prevInput = *this;

    if (cursor.state & Cursor::LEFT || !cursorClock.isRunning())
        cursorClock.restart();

    handleEvents();
    handleKeyboard();
    handleMouseMovement();

    blinkTextCursor = static_cast<int>(cursorClock.millis()) % 1000 < 500;
}

void engix::Input::loadControls()
{
    auto json = json::Value::loadFromFile(assets::DATA_PATH + "controls.json");
    auto foo = json["controls"];
    auto controlsJson = json["controls"].as<std::vector<json::Value>>();
    for (const auto& controlJson : controlsJson)
    {
        assert(controlJson.isMember("function") && controlJson.isMember("key"));
        auto scancode = SDL_GetScancodeFromName(controlJson["key"].as<std::string>().c_str());
        controls[Substr(controlJson["function"].as<std::string>())] = scancode;
    }
}

void engix::Input::handleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_WINDOWEVENT:
            handleWindowEvent(e.window);
            break;
        case SDL_MOUSEBUTTONDOWN:
            handleMouseDown(e.button);
            break;
        case SDL_MOUSEBUTTONUP:
            handleMouseUp(e.button);
            break;
        case SDL_KEYDOWN:
            onKeyDown(e.key);
            break;
        case SDL_KEYUP:
            onKeyUp(e.key);
            break;
        case SDL_TEXTINPUT:
            handleTextInput(e.text);
            break;
        case SDL_MOUSEWHEEL:
            handleScroll(e.wheel);
            break;
        }
    }
}

void engix::Input::handleKeyboard()
{
    auto keyStates = SDL_GetKeyboardState(nullptr);
    for (auto control : controls)
    {
        inputs[control.first] = keyStates[control.second];
    }
}

void engix::Input::handleMouseMovement()
{
    auto prevPosition = cursor.position;
    int x, y;
    SDL_GetMouseState(&x, &y);
    cursor.position = Vector2d(x, y) / roundPixelScale;
    cursor.movement = prevPosition - cursor.position;
}

void engix::Input::handleWindowEvent(const SDL_WindowEvent &e)
{
    switch (e.event)
    {
    case SDL_WINDOWEVENT_ENTER:
        cursor.isShown = true;
        break;
    case SDL_WINDOWEVENT_LEAVE:
        cursor.isShown = false;
        break;
    }
}

void engix::Input::handleMouseDown(const SDL_MouseButtonEvent& e)
{
    switch (e.button)
    {
    case SDL_BUTTON_LEFT:
        cursor.state |= Cursor::LEFT;
        break;
    }
}

void engix::Input::handleMouseUp(const SDL_MouseButtonEvent& e)
{
    switch (e.button)
    {
    case SDL_BUTTON_LEFT:
        cursor.state ^= Input::Cursor::LEFT;
        break;
    }
}

void engix::Input::handleScroll(const SDL_MouseWheelEvent &e)
{
    cursor.scroll += e.y;
}

void engix::Input::handleTextInput(const SDL_TextInputEvent &e)
{
    constexpr encoding::Format FORMAT(encoding::UTF8,
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    encoding::UTF16BE
    #else
    encoding::UTF16LE
    #endif
    );

    auto insertedText = encoding::convert<char, char16_t>(std::string(e.text), FORMAT);
    text.insert(textCursor, insertedText);
    textCursor += static_cast<int>(insertedText.size());
}

void engix::Input::onKeyDown(const SDL_KeyboardEvent &e)
{
    if (isReading)
    {
        cursorClock.restart();   
        switch (e.keysym.scancode)
        {
            case SDL_SCANCODE_BACKSPACE:
            {
                if (text.size() == 0)
                    break;
                
                auto index = textCursor - 1;
                text.erase(index, 1);
                textCursor--;
            }
            break;
            case SDL_SCANCODE_LEFT:
                onLeftDown(e);
            break;
            case SDL_SCANCODE_RIGHT:
                onRightDown(e);
            break;
            case SDL_SCANCODE_LSHIFT:
                shift = true;
            break;
            case SDL_SCANCODE_LCTRL:
                ctrl = true;
            break;
        }
    }
}

void engix::Input::onKeyUp(const SDL_KeyboardEvent &e)
{
    switch (e.keysym.scancode)
    {
    case SDL_SCANCODE_LSHIFT:
        shift = false;
        break;
    case SDL_SCANCODE_LCTRL:
        ctrl = false;
        break;
    }
}

void engix::Input::onLeftDown(const SDL_KeyboardEvent &e)
{
    if (textCursor == 0)
        return;

    int movement = ctrl ? textCursor : 1;
    textCursor -= movement;
}

void engix::Input::onRightDown(const SDL_KeyboardEvent &e)
{
    if (textCursor == text.size())
        return;

    int movement = ctrl ? static_cast<int>(text.size()) - textCursor : 1;
    textCursor += movement;
}
