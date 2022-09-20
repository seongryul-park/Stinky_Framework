#pragma once
#include "VAO.hpp"
#include <glad/glad.h>

namespace Stinky
{
	VAO::VAO()
	{
		glGenVertexArrays(1, &ID);
		glBindVertexArray(ID);
	}

	void VAO::LinkAttrib(VBO vbo, unsigned int layout, unsigned int numComponenets, unsigned int type, int stride, void* offset)
	{
		vbo.Bind();

		glVertexAttribPointer(layout, numComponenets, type, GL_FALSE, stride, offset);
		glEnableVertexAttribArray(layout);

		vbo.UnBind();
	}

	void VAO::Bind()
	{
		glBindVertexArray(ID);
	}

	void VAO::UnBind()
	{
		glBindVertexArray(0);
	}

	void VAO::Delete()
	{
		glDeleteVertexArrays(0, &ID);
	}
}