#pragma once
#include "Camera.hpp"
#include "Math/Matrix.hpp"

#include  <iostream>
#include <glad/glad.h>

namespace Stinky
{
	void Camera::Init(float widths, float heights)
	{
		frameReference = FrameReference::RightHanded_OriginCenter;

		width = widths;
		height = heights;

		viewMatrix = identity;
		camMatrix = ScaleMatrix(2.f / static_cast<float>(width), 2.f / static_cast<float>(height));

		finalMatrix = camMatrix * viewMatrix;
	}


	void Camera::Update(float widths, float heights)
	{
		frameReference = FrameReference::RightHanded_OriginCenter;

		width = widths;
		height = heights;

		viewMatrix = identity;
		camMatrix = ScaleMatrix(2.f / static_cast<float>(width), 2.f / static_cast<float>(height));

		glViewport(0, 0, static_cast<int>(width), static_cast<int>(height));

		finalMatrix = camMatrix * viewMatrix;
	}

	void Camera::SetFrameReference(FrameReference reference)
	{
		frameReference = reference;

		switch (frameReference)
		{
		case FrameReference::RightHanded_OriginCenter:
			viewMatrix = identity;
			break;
		case FrameReference::RightHanded_OriginBottomLeft:
			viewMatrix = TranslateInverseMatrix(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
			break;
		case FrameReference::LeftHanded_OriginTopLeft:
			viewMatrix = ScaleInverseMatrix(1, -1) * TranslateInverseMatrix(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
			break;
		default:
			break;
		}

		finalMatrix = camMatrix * viewMatrix;
	}

	FrameReference Camera::GetFrameReference()
	{
		return frameReference;
	}

	glm::mat3 Camera::GetCameraMatrix() const
	{
		return finalMatrix;
	}
}