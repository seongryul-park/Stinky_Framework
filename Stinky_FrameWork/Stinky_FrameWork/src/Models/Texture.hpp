#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "../Stinky/Shader.hpp"

namespace Stinky
{
	class Texture
	{
	public:
		//	 texture's ID
		unsigned int ID;
		unsigned int type;

		//	texture's width, height
		int width;
		int height;
		int Colch;

		//	make initial texture class
		Texture();

		//	read image file and save in GraphicEngine
		void init(const char* image, unsigned int texType, unsigned int format, unsigned int pixelType);
		//	what kind of the GL_TEXTURE use
		void texUnit(Stinky::Shader& shader, const char* uniform, unsigned int unit);
		//	Active texture
		void Active();

		void Bind();
		void UnBind();
		void Delete();
	};
}

#endif