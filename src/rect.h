#pragma once

#include "vector2.h"
#include <SDL.h>
#include "math.h"
#include "color.h"

namespace engix
{
    extern SDL_Renderer* gRenderer;
    extern double pixelScale;
    extern double roundPixelScale;

    struct Rect
    {
        Vector2i start;
        int width = 0;
        int height = 0;

        constexpr Rect() noexcept {}
        constexpr Rect(int x, int y, int width, int height) noexcept:
            start(x, y), width(width), height(height) {}
        constexpr Rect(Vector2i start, int width, int height) noexcept :
            start(start), width(width), height(height) {}
        constexpr Rect(int width, int height) noexcept :
            start(), width(width), height(height) {}
        constexpr Rect(Vector2i a, Vector2i b) noexcept :
            start(std::min(a.x, b.x), std::min(a.y, b.y)), width(abs(a.x - b.x)), height(abs(a.y - b.y)) {}
        Rect(const json::Value& json) noexcept : Rect(fromJson(json)) {}

        constexpr bool isAbove(Vector2i point) const noexcept
        {
            return start.x <= point.x && start.x + static_cast<int>(width) >= point.x &&
                start.y <= point.y && start.y + static_cast<int>(height) >= point.y;
        }
        constexpr static bool checkIntersection(Rect a, Rect b) noexcept
        {
            return !(a.start.x + a.width <= b.start.x || b.start.x + b.width <= a.start.x 
                || a.start.y + a.height <= b.start.y || b.start.y + b.height <= a.start.y);
        }
        constexpr static Rect intersection(Rect a, Rect b) noexcept
        {
            auto aleft = a.start.x;
            auto aright = aleft + a.width;
            auto aup = a.start.y;
            auto adown = aup + a.height;

            auto bleft = b.start.x;
            auto bright = bleft + b.width;
            auto bup = b.start.y;
            auto bdown = bup + b.height;

            if (aright <= bleft || bright <= aleft || adown <= bup || bdown <= aup)
                return {};

            auto left = std::max(aleft, bleft);
            auto right = std::min(aright, bright);
            auto up = std::max(aup, bup);
            auto down = std::min(adown, bdown);
            
            return {left, right, right - left, down - up};
        }

        void render(Color color) const noexcept;
        
        constexpr operator SDL_Rect() const noexcept {return {start.x, start.y, static_cast<int>(width), static_cast<int>(height)};}

        json::Value toJson() const noexcept
        {
            json::Value json;
            json["start"] = start;
            json["width"] = width;
            json["height"] = height;
            return json;
        }
        operator json::Value() const noexcept {return toJson();}

        constexpr bool operator==(Rect rect) const noexcept
        {return start == rect.start && width == rect.width && height == rect.height;}
        constexpr operator bool() const noexcept {return *this != Rect();}

        static Rect fromJson(const json::Value& json) noexcept
        {
            Rect result;
            result.start = Vector2i::fromJson(json["start"]);
            result.width = json.get("width", 0).as<int>();
            result.height = json.get("height", 0).as<int>();
            return result;
        }
    };
}