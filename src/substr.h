#pragma once

#include <type_traits>
#include <string>
#include <cassert>

namespace engix
{
    template <class C>
    class StrWrap
    {
    public:
        using String = std::basic_string<C>;
        using C_str = const C*;

        constexpr StrWrap(C_str ptr) noexcept : _ptr(ptr) {}
        StrWrap(const String& str) noexcept : _ptr(str.c_str()) {}

        constexpr C operator[](size_t index) const noexcept {return _ptr[index];}
        constexpr StrWrap operator+(size_t index) const noexcept {return _ptr + index;}
        constexpr void operator+=(size_t index) noexcept {_ptr += index;}
        constexpr void operator-=(size_t index) noexcept {_ptr -= index;}
        constexpr StrWrap operator++() noexcept {return ++_ptr;}
        constexpr StrWrap operator++(int) noexcept {return _ptr++;}
        constexpr StrWrap operator--() noexcept {return --_ptr;}
        constexpr StrWrap operator--(int) noexcept {return --_ptr;}
    public:
        constexpr C_str c_str() const noexcept {return _ptr;}
        constexpr void c_str(C_str ptr) noexcept {_ptr = ptr;}

        constexpr operator C_str() const noexcept {return _ptr;}
        
        constexpr String to_str() const noexcept {return String(_ptr);}
    private:
        C_str _ptr;
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

        constexpr Substr(StrWrap<C> str) noexcept
        : Substr(str.c_str()) {}

        constexpr size_t find(C c) const noexcept {return std::find(_begin, _end, c);}
        constexpr size_t findSize() const noexcept {return std::distance(_begin, _end);}
        
        String toString() const noexcept
        {
            return {_begin, _end};
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

        static constexpr bool compare(Substr a, Substr b) noexcept
        {
            auto aIt = a._begin;
            auto bIt = b._begin;

            while (true)
            {
                if (aIt == a._end)
                    return bIt == b._end;
                if (bIt == b._end)
                    return false;
                if (toupper(*aIt) != toupper(*bIt))
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
    size_t operator()(const engix::Substr<T>& substr) const noexcept
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