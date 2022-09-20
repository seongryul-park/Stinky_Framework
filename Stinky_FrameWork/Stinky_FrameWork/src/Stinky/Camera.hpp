#pragma once

#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

#include "FrameReferences.hpp"

namespace Stinky
{
	class Camera
	{
	private:
		FrameReference frameReference;

		glm::mat3 viewMatrix;
		glm::mat3 camMatrix;
		glm::mat3 finalMatrix;

		float width;
		float height;

	public:
		void Init(float width, float height);
		void Update(float width, float height);

		//	set camers's frame reference
		void SetFrameReference(FrameReference);
		//	return camera's frame reference
		FrameReference GetFrameReference();
		//	return camera's finalMatrix
		glm::mat3 GetCameraMatrix() const;
	};
}
