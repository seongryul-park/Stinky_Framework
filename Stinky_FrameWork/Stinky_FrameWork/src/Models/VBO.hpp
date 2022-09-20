#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "DrawElement.hpp"

namespace Stinky
{
	class VBO : public DrawElement
	{
	public:
		//	using indices make vbo
		VBO(float* vertices, int size);

		void Bind() override;
		void UnBind() override;
		void Delete() override;
	};
}

#endif