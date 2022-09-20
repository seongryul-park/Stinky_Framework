#pragma once

namespace Stinky
{
    struct Color
    {
        float red{ 0.f };
        float green{ 0.f };
        float blue{ 0.f };
        float alpha{ 255.f };

        Color() = default;

        Color(float grey, float alpha = 255)
            : red(grey), green(grey), blue(grey), alpha(alpha) {   }

        Color(float red, float green, float blue, float alpha = 255)
            : red(red), green(green), blue(blue), alpha(alpha) {   }
    };

    struct HexColor
    {
        unsigned int rgba = 0x000000ff;

        HexColor() = default;
        HexColor(unsigned int hex) : rgba(hex) {}

        operator Color()
        {
            return Color
            {
                //  FF000000
                static_cast<float>((rgba & 0xff000000) >> 24),
                //  00FF0000
                static_cast<float>((rgba & 0x00ff0000) >> 16),
                //  0000FF00
                static_cast<float>((rgba & 0x0000ff00) >> 8),
                //  000000FF
                static_cast<float>((rgba & 0x000000ff) >> 0)
            };
        }
    };

    struct ColorNDC
    {
        float red;
        float green;
        float blue;
        float alpha;

        ColorNDC(Color color)
            //  rgba's color convert to NDC variables
            : red(color.red / 255), green(color.green / 255), blue(color.blue / 255), alpha(color.alpha / 255) {   }
    };
}