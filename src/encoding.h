#pragma once

#include <SDL.h>
#include <string>
#include <cassert>
#include <cstring>
#include <unordered_map>
#include <memory>
#include <type_traits>
#include "substr.h"

using std::strcmp;

namespace engix
{
    namespace encoding
    {
        enum Encoding : uint8_t {LE = 0b0, BE = 0b1, UTF8 = 0b10, UTF16LE = 0b100, UTF16BE = 0b101, UTF32LE = 0b110, UTF32BE = 0b111};
        struct Format
        {
            Encoding from;
            Encoding to;

            constexpr Format(Encoding from = UTF8, Encoding to = UTF8) noexcept : from(from), to(to) {}
            constexpr Format(Substr<char> from, Substr<char> to) noexcept : from(encodingFromStr(from)), to(encodingFromStr(to)) {}

            constexpr bool operator==(const Format& format) const noexcept {return from == format.from && to == format.to;}
        
            constexpr static Encoding encodingFromStr(Substr<char> str) noexcept
            {
                if (str == "UTF-16LE")
                    return Encoding::UTF16LE;
                if (str == "UTF-16BE")
                    return Encoding::UTF16BE;
                if (str == "UTF-32LE")
                    return Encoding::UTF32LE;
                if (str == "UTF-32BE")
                    return Encoding::UTF32BE;
                return Encoding::UTF8;
            }
            constexpr static const char* strFromEncoding(Encoding encoding) noexcept
            {
                switch (encoding)
                {
                case UTF16LE:
                    return "UTF-16LE";
                case UTF16BE:
                    return "UTF-16BE";
                case UTF32LE:
                    return "UTF-32LE";
                case UTF32BE:
                    return "UTF-32BE";
                default:
                    return "UTF-8";
                }
            }
        };

        inline constexpr size_t hashFormat(const Format& format)
        {
            return static_cast<size_t>(format.from) | (static_cast<size_t>(format.to) << 8);
        }

        template <class FromChar, class ToChar>
        auto convert(const std::basic_string<FromChar>& from, Format format)
        {
            static std::unordered_map<Format, SDL_iconv_t, decltype(&hashFormat)> descriptors(0, hashFormat);

            if (!descriptors.contains(format))
            {
                descriptors[format] = SDL_iconv_open(Format::strFromEncoding(format.to), Format::strFromEncoding(format.from));
            }
            if (from.size() == 0)
            {
                return std::basic_string<ToChar>();
            }

            size_t inBytes = from.size() * sizeof(FromChar);
            size_t outBytes = std::max(from.size() * sizeof(ToChar), inBytes);

            std::basic_string<ToChar> result(outBytes, 0);
            auto out = reinterpret_cast<char*>(result.data());
            auto in = reinterpret_cast<const char*>(from.data());

            SDL_iconv(descriptors[format], &in, &inBytes, &out, &outBytes);
            result = result.c_str();
            return result;
        }
    }
}