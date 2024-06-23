#pragma once

#include "substr.h"

namespace engix
{
    class Control
    {
    public:
        enum Value : uint8_t
        {
            LEFT,
            RIGHT,
            UP,
            DOWN
        };
        constexpr Control() noexcept {}
        constexpr Control(Value val) noexcept : value(val) {}
        Control(Substr<char> str) noexcept : value(fromStr(str)) {}

        constexpr operator Value() const noexcept { return value; }

        constexpr bool operator==(Control a) const { return value == a.value; }
        constexpr bool operator!=(Control a) const { return value != a.value; }
        
        static Value fromStr(Substr<char> str)
        {
            if (str == "left")
                return LEFT;
            if (str == "up")
                return UP;
            if (str == "right")
                return RIGHT;
            if (str == "down")
                return DOWN;
            assert(false);
        }
        static constexpr const char* toStr(Value val) noexcept
        {
            switch (val)
            {
            case LEFT: return "left";
            case UP: return "up";
            case RIGHT: return "right";
            case DOWN: return "down";
            }
            return "";
        }
        constexpr const char* toStr() const noexcept {return toStr(value); }
    protected:
        Value value;
    };
}
    
template<>
struct std::hash<engix::Control>
{
    size_t operator()(engix::Control control) const noexcept
    {
        return static_cast<size_t>(static_cast<engix::Control::Value>(control));
    }
};