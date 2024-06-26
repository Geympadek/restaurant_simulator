#include "color.h"
#include <sstream>
#include <cstring>
#include <stdexcept>

using namespace engix;

const Color Color::WHITE(255, 255, 255);
const Color Color::BLACK(0, 0, 0);
const Color Color::RED(255, 0, 0);
const Color Color::GREEN(0, 255, 0);
const Color Color::BLUE(0, 0, 255);
const Color Color::CYAN(0, 255, 255);
const Color Color::TRANSPARENT(0, 0, 0, 0);

void engix::Color::loadFromString(Substr<char> str) noexcept
{
    auto size = str.findSize();
    if (size == 1)

    if (str[0] == '#')
        str.begin()++;
    
    uint32_t color = str.toHex();
    switch (size)
    {
    case 6:
        loadFromHex((color << 8) | 0xff);
        break;
    case 4:
        loadFromHex((color << 16) | (color << 8) | 0xff);
        break;
    case 2:
        loadFromHex((color << 24) | (color << 16) | (color << 8) | 0xff);
        break;
    default:
        loadFromHex(color);
        break;
    }
}

constexpr void engix::Color::loadFromHex(uint32_t color) noexcept
{
    red = color >> 24;
    green = color >> 16;
    blue = color >> 8;
    alpha = color;
}