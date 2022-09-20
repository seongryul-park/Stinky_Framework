#pragma once
#include <iostream>

#include "src/Stinky/Stinky.hpp"
using namespace Stinky;

int main()
{
    {
        CreateWindow(1000, 800);

        while (!IsWindowClosed())
        {
            UpdateWindow();
            ClearBackground(Color{ 20, 255, 255, 255 });

            //NoOutline();
                       
            SetTintColor(Color{ 255, 0, 0, 255 });
            DrawImage("../image/Garrosh.jpg", 0, 0);
            //  DrawImage("../image/slime.png", 0, 0);

            Width /= 2;

            PushSetting();
            SetFillColor(Stinky::Color{ 255, 200, 200, 255 });
            SetOutlineColor(Color{ 255 });
            SetOutlineWidth(10);
            //DrawRect(0, 0, static_cast<float>(Width) / 2, static_cast<float>(Width) / 2);
            PopSetting();

            //SetOutlineColor(Color{ 0 });
            //SetFillColor(Color{ 0, 100, 200 });
            //DrawRect(0, 0, static_cast<float>(Width) / 2, static_cast<float>(Width) / 2);
        }
    }
}
