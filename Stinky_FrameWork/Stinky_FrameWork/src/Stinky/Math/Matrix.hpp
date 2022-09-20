#pragma once
#include <glm/mat3x3.hpp>
namespace Stinky
{
	//	apply Matrix3x3 inner GraphicEngins's matrix
	void ApplyScale(float xSize, float ySize);

	void ApplyScale(glm::vec2 vec2);


	void ApplyRotate(float angle);


	void ApplyTranslate(float xPos, float yPos);

	void ApplyTranslate(glm::vec2 vec2);


	//	return Matrix3x3
	glm::mat3 ScaleMatrix(float xSize, float ySize);

	glm::mat3 RotateMatrix(float angle);

	glm::mat3 TranslateMatrix(float xSize, float ySize);

	glm::mat3 ScaleMatrix(glm::vec2 v2);

	glm::mat3 TranslateMatrix(glm::vec2 v2);


	//	identity
	constexpr glm::mat3 identity{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };


	//	Apply Inverse Matrix3x3 inner GraphicEngins's matrix
	void ApplyInverseScale(float xSize, float ySize);

	void ApplyInverseScale(glm::vec2 vec2);


	void ApplyInverseRotate(float angle);


	void ApplyInverseTranslate(float xPos, float yPos);

	void ApplyInverseTranslate(glm::vec2 vec2);


	//	 return inverse Matrix3x3
	glm::mat3 ScaleInverseMatrix(float xSize, float ySize);

	glm::mat3 RotateInverseMatrix(float angle);

	glm::mat3 TranslateInverseMatrix(float xSize, float ySize);

	glm::mat3 ScaleInverseMatrix(glm::vec2 v2);

	glm::mat3 TranslateInverseMatrix(glm::vec2 v2);
}