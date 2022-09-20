#pragma once
#include "EBO.hpp"
#include <glad/glad.h>

namespace Stinky
{
	EBO::EBO(unsigned int* indices, int size)
	{
		glGenBuffers(1, &ID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
	}

	void EBO::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	}

	void EBO::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void EBO::Delete()
	{
		glDeleteBuffers(1, &ID);
	}
}