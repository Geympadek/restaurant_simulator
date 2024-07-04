#include "animation.h"

using namespace engix;

Animation::~Animation()
{
    free();
}

Animation Animation::load(const assets::Path &path)
{
    Animation animation;

    animation._sheet = Texture::load(path + ".png");
    
    auto json = json::Value::loadFromFile(path + ".json");
    animation.loadDelays(json);
    animation._orientation = (json["orientation"].as<std::string>() == "vertical" ? Orientation::VERTICAL : Orientation::HORIZONTAL);

    animation._width = animation._sheet.width();
    animation._height = animation._sheet.height();
    (animation._orientation == Orientation::HORIZONTAL ? animation._width : animation._height) /= animation._numberOfFrames;

    animation._isLoaded = true;
    return animation;
}

void engix::Animation::loadDelays(const json::Value &json)
{
    const auto& jsonDelays = json["delays"].as<std::vector<long double>>();
    
    _duration = 0.0l;
    _numberOfFrames = json.get("number_frames", jsonDelays.size()).as<int>();
    _delays.resize(_numberOfFrames, 0.0l);
    for (int i = 0; i < _numberOfFrames; i++)
    {
        int index = i % jsonDelays.size();
        _delays[i] = jsonDelays[index];
        _duration += _delays[i];
    }
}

void engix::Animation::free() noexcept
{
    if (!_isLoaded)
        return;
    _isLoaded = false;
    
    _sheet.free();
    _delays = {};
    _numberOfFrames = 0;
    _width = 0;
    _height = 0;
    _duration = 0;
}

void engix::Animation::render(long double millis, Vector2i position, double scale, Rotation rotation, Vector2i center, Texture::Flip flip) const
{
    render(millis, position, Rect(0, 0, _width, _height), scale, rotation, center, flip);
}

void engix::Animation::render(long double millis, Vector2i position, Rect clip, double scale, Rotation rotation, Vector2i center, Texture::Flip flip) const
{
    if (!_isLoaded)
        return;

    int frame = 0;
    long double delay = 0;
    while (true)
    {
        if (frame >= _numberOfFrames)
        {
            frame--;
            break;
        }
        delay += _delays[frame];
        if (millis < delay)
        {
            break;
        }
        frame++;
    }
    Vector2i offset;
    if (_orientation == Orientation::HORIZONTAL)
        offset.x = _width * frame;
    else
        offset.y = _height * frame;
    Rect renderClip(offset + clip.start, clip.width, clip.height);
    _sheet.render(position, renderClip, scale, rotation, center, flip);
}
