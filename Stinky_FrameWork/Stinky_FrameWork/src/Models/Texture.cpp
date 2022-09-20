#pragma once

#include "Texture.hpp"
#include <iostream>

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include<stb/stb_image.h>


namespace Stinky
{
	Texture::Texture()
		: ID(0), type(GL_TEXTURE_2D), width(0), height(0), Colch(0)
	{	
		glGenTextures(1, &ID);
	}

	void Texture::init(const char* image, unsigned int texType, unsigned int format, unsigned int pixelType)
	{
		type = texType;

		// stb_image and opengl read different order
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(image, &width, &height, &Colch, STBI_rgb_alpha);
	
		Active();

		/*
		glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);
		*/

		
		if (data)
		{
			glTexImage2D(texType, 0, GL_RGBA, width, height, 0, format, pixelType, data);
			glGenerateMipmap(texType);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		
		stbi_image_free(data);
		UnBind();
	}

	void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
	{
		GLuint texUni = glGetUniformLocation(shader.ID, uniform);

		glUniform1i(texUni, unit);
	}

	void Texture::Active()
	{
		glActiveTexture(GL_TEXTURE0);
		Bind();
	}

	void Texture::Bind()
	{
		glBindTexture(type, ID);
	}

	void Texture::UnBind()
	{
		glBindTexture(type, 0);
	}

	void Texture::Delete()
	{
		glDeleteTextures(1, &ID);
	}
}