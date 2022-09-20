#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include <glad/glad.h>
#include "DrawElement.hpp"
#include "VBO.hpp"

namespace Stinky
{
	class VAO : public DrawElement
	{
	public:
		VAO(); 

		//	link with vbo
		void LinkAttrib(VBO vbo, unsigned int layout, unsigned int numComponenets, unsigned int type, int stride, void* offset);

		void Bind() override;
		void UnBind() override;
		void Delete() override;
	};
}

#endif	//	VAO_CLASS_H