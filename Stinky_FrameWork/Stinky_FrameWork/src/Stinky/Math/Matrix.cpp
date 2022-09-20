#pragma once

#include "Matrix.hpp"
#include "../GraphicEngine.hpp"

namespace Stinky
{
	// inner function only use this cpp file
	void ApplyMatrix(glm::mat3 mat, glm::mat3 imat);

	void ApplyScale(float xSize, float ySize)
	{
		ApplyMatrix(ScaleMatrix(xSize, ySize), ScaleInverseMatrix(xSize, ySize));
	}

	void ApplyScale(glm::vec2 v2)
	{
		ApplyScale(v2.x, v2.y);
	}

	void ApplyRotate(float angle)
	{
		ApplyMatrix(RotateMatrix(angle), RotateInverseMatrix(angle));
	}

	void ApplyTranslate(float xPos, float yPos)
	{
		ApplyMatrix(TranslateMatrix(xPos, yPos), TranslateInverseMatrix(xPos, yPos));
	}

	void ApplyTranslate(glm::vec2 v2)
	{
		ApplyTranslate(v2.x, v2.y);
	}

	void ApplyMatrix(glm::mat3 mat, glm::mat3 imat)
	{
		GraphicEngine::GetMatrix() = mat * GraphicEngine::GetMatrix();
		GraphicEngine::GetOptions().top().popMatrix3s *= imat;
	}

	glm::mat3 ScaleMatrix(float xSize, float ySize)
	{
		return glm::mat3{ xSize, 0, 0, 0, ySize, 0, 0, 0, 1 };
	}

	glm::mat3 RotateMatrix(float angle)
	{
		return { cos(angle), sin(angle), 0, -sin(angle), cos(angle), 0, 0, 0, 1 };
	}

	glm::mat3 TranslateMatrix(float xPos, float yPos)
	{
		return  glm::mat3{ 1, 0, 0, 0, 1, 0, xPos, yPos, 1 };
	}

	glm::mat3 ScaleMatrix(glm::vec2 v2)
	{
		return ScaleMatrix(v2.x, v2.y);
	}

	glm::mat3 TranslateMatrix(glm::vec2 v2)
	{
		return TranslateMatrix(v2.x, v2.y);
	}

	void ApplyInverseScale(float xSize, float ySize)
	{
		ApplyScale(1.f / xSize, 1.f / ySize);
	}

	void ApplyInverseScale(glm::vec2 vec2)
	{
		ApplyInverseScale(vec2.x, vec2.y);
	}

	void ApplyInverseRotate(float angle)
	{
		ApplyRotate(-angle);
	}

	void ApplyInverseTranslate(float xPos, float yPos)
	{
		ApplyTranslate(-xPos, -yPos);
	}

	void ApplyInverseTranslate(glm::vec2 vec2)
	{
		ApplyInverseTranslate(vec2.x, vec2.y);
	}

	glm::mat3 ScaleInverseMatrix(float xSize, float ySize)
	{
		return ScaleMatrix(1.f / xSize, 1.f / ySize);
	}

	glm::mat3 RotateInverseMatrix(float angle)
	{
		return RotateMatrix(-angle);
	}

	glm::mat3 TranslateInverseMatrix(float xSize, float ySize)
	{
		return TranslateMatrix(-xSize, -ySize);
	}

	glm::mat3 ScaleInverseMatrix(glm::vec2 v2)
	{
		return ScaleInverseMatrix(v2.x, v2.y);
	}

	glm::mat3 TranslateInverseMatrix(glm::vec2 v2)
	{
		return TranslateInverseMatrix(v2.x, v2.y);
	}
}