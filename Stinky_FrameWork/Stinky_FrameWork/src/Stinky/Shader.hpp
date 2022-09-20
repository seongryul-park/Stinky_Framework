#pragma once
#include <glm/vec2.hpp>

#include <iostream>

namespace Stinky
{
	//	can read vertex or fragment files
	std::string GetFileContents(const char* filename) noexcept;

	class Shader
	{
	public:
		unsigned int ID;

		Shader(const char* vertexFile, const char* fragmentFile);

		void Activate();
		void UnActivate();

		//	send shader to uniform value
		void SetUniform(std::string name, int value);		//	uniform one int value - name is uniform's name
		void SetUniform(std::string name, bool value);		//	uniform one bool value
		void SetUniform(std::string name, float value);		//	uniform one float value
		void SetUniform(std::string name, int value1, int value2);		//	uniform two float values
		void SetUniform(std::string name, float value1, float value2);	//	uniform two float values
		void SetUniform(std::string name, const float* value);
		void SetUniform_MToN_Matrix(glm::vec2 translate, glm::vec2 scale); //	uniform scale and translate values

		void Delete();

	private:
		//	link vertex shader and fragment shader
		unsigned int LinkShader(unsigned int vertexShader, unsigned int fragShader);
	};
}