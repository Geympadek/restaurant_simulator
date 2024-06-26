#include "font.h"

using namespace engix;

static int getCharWidth(const engix::Texture& texture, engix::Rect clip)
{
    const auto& pixels = texture.pixels();
    int maxX = clip.start.x;
    for (int y = clip.start.y; y < clip.start.y + clip.height; y++)
    {
        for (int x = clip.start.x + 1; x < clip.start.x + clip.width; x++)
        {
            if (pixels[x + y * texture.width()].alpha != 0 && maxX < x)
                maxX = x;
        }
    }
    return maxX - clip.start.x;
}

Font engix::Font::load(const assets::Path &path)
{
    Font font;
    font.sheet = Texture::load(path + ".png");
    auto json = json::Value::loadFromFile(path + ".json");

    auto start = Vector2i::fromJson(json["start"]);

    encoding::Format format("utf8", json["format"].as<std::string>().c_str());
    
    auto utf8charList = json["list"].as<std::string>();
    auto charList = encoding::convert<char, char16_t>(utf8charList, format);

    font.cellWidth = json["cell_width"].as<int>();
    font.cellHeight = json["cell_height"].as<int>();
    auto cellShift = Vector2i::fromJson(json["cell_shift"]);

    font._height = json["height"].as<int>();

    font._cursorOffset = Vector2i::fromJson(json["cursor_offset"]);

    font._nextCharShift = json["next_char_shift"].as<int>();

    font._selectedLeft = json["selected_left"].as<int>();
    font._selectedRight = json["selected_right"].as<int>();
    font._selectedHeight = json["selected_height"].as<int>();
    font._selectionOffset = Vector2i::fromJson(json["selection_offset"]);

    int row = 0, column = 0;
    for (auto ch : charList)
    {
        if (ch == u'\n')
        {
            column = 0;
            row++;
            continue;
        }

        auto& currentChar = font._chars[ch];
        currentChar.clip.start = start + Vector2i(column * (font.cellWidth + cellShift.x), row * (font.cellHeight + cellShift.y));
        currentChar.clip.width = font.cellWidth;
        currentChar.clip.height = font.cellHeight;
        currentChar.width = getCharWidth(font.sheet, currentChar.clip);

        column++;
    }

    auto charsJson = json["_chars"].as<std::vector<json::Value>>();
    for (const auto& charJson : charsJson)
    {
        auto utf8 = charJson["char"].as<std::string>();
        auto result = encoding::convert<char, char16_t>(utf8, format);
        auto& charInfo = font._chars[result[0]];
        charInfo.width = charJson["width"].as<int>();
    }
    font._isLoaded = true;
    return font;
}

void engix::Font::free() noexcept
{
    if (!_isLoaded)
        return;
    _isLoaded = false;
    
    sheet.free();
}

Texture engix::Font::createTexture(Substr<char16_t> text, Color color) const
{
    auto size = findSize(text);

    PixelImage pixelImage(size.x, size.y);

    map(text, [&pixelImage, this](Vector2i cursor, char16_t c, size_t i, const CharInfo& cInfo){
        pixelImage.draw(this->sheet.pixelImage(cInfo.clip), cursor);
    });
    return Texture(pixelImage);
}

Vector2i engix::Font::findSize(Substr<char16_t> text) const
{
    int height = 0, width = 0;

    Vector2i cursor;
    for (auto c : text)
    {
        if (c == u'\0')
        {
            continue;
        }
        if (c == u'\n')
        {
            cursor.x = 0;
            cursor.y += cellHeight;
            continue;
        }
        cursor.x += _chars[c].width + _nextCharShift;

        if (width < cursor.x)
            width = cursor.x;
        if (height < cursor.y)
            height = cursor.y;
    }
    return {width + 1, height + cellHeight};
}

size_t engix::Font::findClosest(Substr<char16_t> text, Vector2i point) const
{
    int width = 0;
    int height = 0;

    auto textSize = text.findSize();
    for (size_t i = 0; i < textSize; i++)
    {
        auto c = text[i];
        if (c == u'\0')
        {
            continue;
        }
        if (c == u'\n')
        {
            width = 0;
            height += cellHeight;
            continue;
        }
        auto info = _chars[c];
        Rect rect(width, height, info.width + _nextCharShift, cellHeight);

        if (rect.isAbove(point))
        {
            return i;
        }

        width += info.width + _nextCharShift;
    }
    return textSize;
}

void engix::Font::map(Substr<char16_t> text, const std::function<void(Vector2i, char16_t, size_t, const CharInfo&)>& handle) const
{
    Vector2i cursor;
    
    auto textSize = text.findSize();
    for (size_t i = 0; i < textSize; i++)
    {
        auto c = text[i];
        if (c == u'\0')
        {
            continue;
        }
        if (c == u'\n')
        {
            cursor.y += _height;
            cursor.x = 0;
            continue;
        }
        CharInfo charInfo = _chars[c];

        handle(cursor, c, i, charInfo);
        
        cursor.x += charInfo.width + _nextCharShift;
    }
}

void engix::Font::render(Substr<char16_t> text, Vector2i position, Color color) const
{
    if (!_isLoaded)
        return;

    const_cast<Font*>(this)->sheet.setColor(color);

    auto cursor = position;

    for (auto c : text)
    {
        if (c == u'\0')
        {
            continue;
        }
        if (c == u'\n')
        {
            cursor.y += _height;
            cursor.x = position.x;
            continue;
        }
        CharInfo charInfo = _chars[c];
        sheet.render(cursor, charInfo.clip);
        cursor.x += charInfo.width + _nextCharShift;
    }
}

void engix::Font::render(Substr<char16_t> text, Vector2i position, Color color, const std::set<size_t> &alternativeChars, Color altColor) const
{
    if (!_isLoaded)
        return;
    
    Color currentColor;

    auto cursor = position;

    size_t index = 0;
    for (auto c : text)
    {
        if (c == u'\0')
        {
            continue;
        }
        if (c == u'\n')
        {
            cursor.y += _height;
            cursor.x = position.x;
            continue;
        }
        Color charColor = (alternativeChars.contains(index) ? altColor : color);
        if (charColor != currentColor)
        {
            currentColor = charColor;
            const_cast<Font*>(this)->sheet.setColor(currentColor);
        }
        CharInfo charInfo = _chars[c];
        sheet.render(cursor, charInfo.clip);
        cursor.x += charInfo.width + _nextCharShift;

        index++;
    }
}