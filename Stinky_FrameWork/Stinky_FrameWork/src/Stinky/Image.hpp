#pragma once
#include <map>
#include <iostream>
#include "Color.hpp"
#include "../Models/Texture.hpp"

namespace Stinky
{
    class Image
    {
    public:
        Image(std::string);
        
    private:
        std::map<std::string, Texture>::iterator textures;

        friend void DrawImage(Image images, float x, float y);
        friend void DrawImage(Image images, float x, float y, float width, float height);
        friend void DrawImage(Image images, float x, float y, float width, float height, float texel_x, float texel_y);
        friend void DrawImage(Image images, float x, float y, float width, float height, float texel_x, float texel_y, float texel_width, float texel_height);
    };

	//	image's filepath, position
    void DrawImage(std::string filepath, float x, float y);
    void DrawImage(Image images, float x, float y);
	//	image's filepath, position, scale
    void DrawImage(std::string filepath, float x, float y, float width, float height);
    void DrawImage(Image images, float x, float y, float width, float height);
	/*
        	Image
          (0,0)
            +------------------------------------------------------------+
            |                                                            |
            |(texel_x,texel_y)                                           |
            |        o-----------------------+                           |
            |        |                       |                           |
            |        |                       |                           |
            |        +-----------------------o                           |
            |                  (texel_x+width,texel_y+height)            |
            |                                                            |
            |                                                            |
            |                                                            |
            +------------------------------------------------------------+
                                                             (image_width,image_height)
    */
    void DrawImage(std::string filepath, float x, float y, float width, float height, float texel_x, float texel_y);
    void DrawImage(Image images, float x, float y, float width, float height, float texel_x, float texel_y);
    /*
                Image
          (0,0)
            +---------------------------------------------------------------------+
            |                                                                     |
            |(texel_x,texel_y)                                                    |
            |        o--------------------------------+                           |
            |        |                                |                           |
            |        |                                |                           |
            |        |                                |                           |
            |        |                                |                           |
            |        |                                |                           |
            |        +--------------------------------o                           |
            |                     (texel_x+texel_width,texel_y+texel_height)      |
            |                                                                     |
            |                                                                     |
            |                                                                     |
            +---------------------------------------------------------------------+
                                                                      (image_width,image_height)
    */
    void DrawImage(std::string filepath, float x, float y, float width, float height, float texel_x, float texel_y, float texel_width, float texel_height);
    void DrawImage(Image images, float x, float y, float width, float height, float texel_x, float texel_y, float texel_width, float texel_height);

    void SetTintColor(Color color);
    void NoTint();
}