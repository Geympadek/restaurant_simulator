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

static constexpr uint8_t hexFromChar(char c)
{
    switch (Substr<char>::tolower(c))
    {
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
    case 'a': return 0xa;
    case 'b': return 0xb;
    case 'c': return 0xc;
    case 'd': return 0xd;
    case 'e': return 0xe;
    case 'f': return 0xf;
    }
    throw std::invalid_argument("Unexpected char in hex conversion.");
}

static constexpr uint32_t hexFromString(Substr<char> str)
{
    uint32_t hex = 0;
    
    for (auto c : str)
    {
        if (hex == 0 && c == '0')
        {
            continue;
        }
        hex <<= 4;
        auto value = hexFromChar(c);
        hex += value;
    }
    return hex;
}

void engix::Color::loadFromString(Substr<char> str) noexcept
{
    auto size = str.findSize();
    if (size == 1)

    if (str[0] == '#')
        str.begin()++;
    
    uint32_t color = hexFromString(str);
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