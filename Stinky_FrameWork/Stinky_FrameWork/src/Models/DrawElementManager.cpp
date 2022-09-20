#pragma once
#include <iostream>

#include "DrawElementManager.hpp"
#include "VAO.hpp"

namespace Stinky
{
	DrawElementManager::DrawElementManager()
		:vao(nullptr) {	}

	void DrawElementManager::Add(DrawElement* elements)
	{
		drawElements.push_back(elements);

		VAO* ptr = GetDrawElement<VAO>(elements);

		if (ptr != nullptr)
		{
			vao = ptr;
		}
	}

	DrawElementManager::~DrawElementManager()
	{
		for (DrawElement* elements : drawElements)
		{
			if (elements != nullptr)
			{
				delete elements;	//	RAII
				elements = nullptr;
			}

			drawElements.clear();
		}
	}

	void DrawElementManager::VAOBind()
	{
		if (vao == nullptr)
		{
			std::cout << "Doesn't have vao!!! - VAO_BIND\n";
		}
		else
		{
			vao->Bind();
		}
	}

	void DrawElementManager::VAOLinkAttrib(VBO* vbo, unsigned int layout, unsigned int numComponenets, unsigned int type, int stride, void* offset)
	{
		if (vao == nullptr)
		{
			std::cout << "Doesn't have vao!!!  - VAO_LINK_ATTRIB\n";
		}
		else
		{
			vao->LinkAttrib(*vbo, layout, numComponenets, type, stride, offset);
		}
	}

	void DrawElementManager::VAOUnBind()
	{
		if (vao == nullptr)
		{
			std::cout << "Doesn't have vao!!!  - VAO_UNBIND\n";
		}
		else
		{
			vao->UnBind();
		}
	}

	void DrawElementManager::BindAll()
	{
		for (DrawElement* elements : drawElements)
		{
			elements->Bind();
		}
	}

	void DrawElementManager::UnBindAll()
	{
		for (DrawElement* elements : drawElements)
		{
			elements->UnBind();
		}
	}

	void DrawElementManager::DeleteAll()
	{
		for (DrawElement* elements : drawElements)
		{
			elements->Delete();
		}
	}
}