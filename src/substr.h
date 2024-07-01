#pragma once

#include <type_traits>
#include <string>
#include <cassert>
#include <stdexcept>

namespace engix
{
    template <class C>
    class CharTraits
    {
    public:
        static constexpr uint8_t hexFromChar(C c)
        {
            if constexpr (std::is_same_v<C, char>)
            {
                switch (tolower(c))
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
            }
            else if constexpr (std::is_same_v<C, char16_t>) 
            {
                switch (tolower(c))
                {
                    case u'0': return 0;
                    case u'1': return 1;
                    case u'2': return 2;
                    case u'3': return 3;
                    case u'4': return 4;
                    case u'5': return 5;
                    case u'6': return 6;
                    case u'7': return 7;
                    case u'8': return 8;
                    case u'9': return 9;
                    case u'a': return 0xa;
                    case u'b': return 0xb;
                    case u'c': return 0xc;
                    case u'd': return 0xd;
                    case u'e': return 0xe;
                    case u'f': return 0xf;
                }
            }
            else if constexpr (std::is_same_v<C, char32_t>)
            {
                switch (tolower(c))
                {
                    case U'0': return 0;
                    case U'1': return 1;
                    case U'2': return 2;
                    case U'3': return 3;
                    case U'4': return 4;
                    case U'5': return 5;
                    case U'6': return 6;
                    case U'7': return 7;
                    case U'8': return 8;
                    case U'9': return 9;
                    case U'a': return 0xa;
                    case U'b': return 0xb;
                    case U'c': return 0xc;
                    case U'd': return 0xd;
                    case U'e': return 0xe;
                    case U'f': return 0xf;
                }
            }
            else if constexpr (std::is_same_v<C, wchar_t>)
            {
                switch (tolower(c))
                {
                    case L'0': return 0;
                    case L'1': return 1;
                    case L'2': return 2;
                    case L'3': return 3;
                    case L'4': return 4;
                    case L'5': return 5;
                    case L'6': return 6;
                    case L'7': return 7;
                    case L'8': return 8;
                    case L'9': return 9;
                    case L'a': return 0xa;
                    case L'b': return 0xb;
                    case L'c': return 0xc;
                    case L'd': return 0xd;
                    case L'e': return 0xe;
                    case L'f': return 0xf;
                }
            }
            throw std::invalid_argument("Unexpected char in hex conversion.");
        }
        static constexpr C toupper(C c) noexcept
        {
            if constexpr (std::is_same_v<C, char>)
            {
                if (c >= 'a' && c <= 'z')
                {
                    return c - ('a' - 'A');
                }
            }
            else if constexpr (std::is_same_v<C, char16_t>) 
            {
                if (c >= u'a' && c <= u'z')
                {
                    return c - (u'a' - u'A');
                }
            }
            else if constexpr (std::is_same_v<C, char32_t>)
            {
                if (c >= U'a' && c <= U'z')
                {
                    return c - (U'a' - U'A');
                }
            }
            else if constexpr (std::is_same_v<C, wchar_t>)
            {
                if (c >= L'a' && c <= L'z')
                {
                    return c - (L'a' - L'A');
                }
            }
            return c;
        }
        static constexpr C tolower(C c) noexcept
        {
            if constexpr (std::is_same_v<C, char>)
            {
                if (c >= 'A' && c <= 'Z')
                {
                    return c + ('a' - 'A');
                }
            }
            else if constexpr (std::is_same_v<C, char16_t>) 
            {
                if (c >= u'A' && c <= u'Z')
                {
                    return c + (u'a' - u'A');
                }
            }
            else if constexpr (std::is_same_v<C, char32_t>)
            {
                if (c >= U'A' && c <= U'Z')
                {
                    return c + (U'a' - U'A');
                }
            }
            else if constexpr (std::is_same_v<C, wchar_t>)
            {
                if (c >= L'A' && c <= L'Z')
                {
                    return c + (L'a' - L'A');
                }
            }
            return c;
        }
    };
    //Simple replacement to const char strings.
    template <class C>
    class C_Str
    {
        using Ptr = const C*;
    public:
        constexpr C_Str(Ptr ptr) noexcept : _ptr(ptr) {}

        constexpr size_t size() const noexcept {return std::char_traits<C>::length(_ptr);} 
        
        constexpr bool operator==(C_Str str) const noexcept
        {
            auto a = _ptr;
            auto b = str._ptr;

            while (true)
            {
                if (CharTraits<C>::toupper(*a) != CharTraits<C>::toupper(*b))
                    return false;
                if (*a == 0)
                    return true;
                a++;
                b++;
            }
        }

        constexpr Ptr c_str() const noexcept {return _ptr;}

        constexpr operator Ptr() const noexcept {return _ptr;}
    private:
        Ptr _ptr;
    };

    template <class C>
    class Substr
    {
    public:
        using Iterator = const C*;
        using String = std::basic_string<C>;

        constexpr Substr() : _begin(nullptr), _end(nullptr) {}
        Substr(String::const_iterator begin, String::const_iterator end) noexcept
        {
            if (begin == end)
            {
                _begin = _end = nullptr;
            }
            else
            {
                _begin = &*begin;
                _end = _begin + std::distance(begin, end);
            }
        }
        constexpr Substr(Iterator begin, Iterator end) noexcept
        : _begin(begin), _end(end) {}
        
        Substr(const String& str) noexcept
        : Substr(str.begin(), str.end()) {}

        constexpr Substr(const C* c_str) noexcept
        : _begin(c_str), _end(_begin + std::char_traits<C>::length(c_str)) {}
        constexpr Substr(const C_Str<C>& c_str) noexcept
        : Substr(c_str) {}

        constexpr size_t find(C c) const noexcept {return std::find(_begin, _end, c);}
        constexpr size_t findSize() const noexcept {return std::distance(_begin, _end);}
        
        String toString() const noexcept
        {
            return {_begin, _end};
        }

        static constexpr uint32_t hexFromString(Substr str)
        {
            uint32_t hex = 0;
            
            for (auto c : str)
            {
                auto value = CharTraits<C>::hexFromChar(c);
                if (hex == 0 && value == 0)
                {
                    continue;
                }
                hex <<= 4;
                hex += value;
            }
            return hex;
        }
        constexpr uint32_t toHex() const
        {
            return hexFromString(*this);
        }

        static constexpr bool compare(Substr a, Substr b) noexcept
        {
            auto aIt = a._begin;
            auto bIt = b._begin;

            while (true)
            {
                bool bIsEnd = bIt == b._end;
                if (aIt == a._end)
                    return bIsEnd;
                if (bIsEnd)
                    return false;
                if (CharTraits<C>::toupper(*aIt) != CharTraits<C>::toupper(*bIt))
                    return false;
                
                aIt++;
                bIt++;
            }
            assert(false);
        }
        static constexpr bool compareCaseSens(Substr a, Substr b) noexcept
        {
            auto aIt = a._begin;
            auto bIt = b._begin;

            while (true)
            {
                if (aIt == a._end)
                    return bIt == b._end;
                if (bIt == b._end)
                    return false;
                if (*aIt != *bIt)
                    return false;
                
                aIt++;
                bIt++;
            }
            assert(false);
        }
        constexpr bool operator==(Substr str) const noexcept
        {
            return compare(*this, str);
        }
        constexpr C operator[](size_t index) const noexcept
        {
            return _begin[index];
        }
    public:
        constexpr Iterator begin() const noexcept {return _begin;}
        constexpr Iterator& begin() noexcept {return _begin;}
        constexpr Iterator end() const noexcept {return _end;}
        constexpr Iterator& end() noexcept {return _end;}
    private:
        Iterator _begin;
        Iterator _end;
    };
}

template<class T>
struct std::hash<engix::Substr<T>>
{
    constexpr size_t operator()(const engix::Substr<T>& substr) const noexcept
    {
        //Some primes
        constexpr size_t A = 54059;
        constexpr size_t B = 76963;
        constexpr size_t FIRSTH = 37;

        size_t h = FIRSTH;
        for (auto c : substr)
        {
            h = (h * A) ^ (static_cast<size_t>(c) * B);
        }
        return h;
    }
};


template<class T>
struct std::hash<engix::C_Str<T>>
{
    constexpr size_t operator()(const engix::C_Str<T>& str) const noexcept
    {
        //Some primes
        constexpr size_t A = 54059;
        constexpr size_t B = 76963;
        constexpr size_t FIRSTH = 37;

        size_t h = FIRSTH;
        for (auto it = str.c_str(); *it != 0; it++)
        {
            h = (h * A) ^ (static_cast<size_t>(*it) * B);
        }
        return h;
    }
};

