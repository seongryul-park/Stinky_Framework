#pragma once
#include "Color.hpp"
#include <glm/vec2.hpp>

#include <iostream>

namespace Stinky
{
	//	Drawing Ellipase
	void DrawEllipse(float xPos, float yPos, float xSize, float ySize);
	void DrawEllipse(glm::vec2 v1, glm::vec2 v2);

	//	Drawing Rectangle
	void DrawRect(float xPos, float yPos, float xSize, float ySize);
	void DrawRect(glm::vec2 v1, glm::vec2 v2);

	//	Setting inner filled color
	void SetFillColor(Color color);
	void SetFillColor(HexColor color);

	//	Setting outline's color
	void SetOutlineColor(Color color);
	void SetOutlineColor(HexColor color);

	//	change outline's width
	void SetOutlineWidth(float width);

	//	doesn't fill inner models
	void NoFill();

	//	doesn't draw outline
	void NoOutline();

}