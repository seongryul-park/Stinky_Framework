#pragma once

#include "../Models/DrawElementManager.hpp"

namespace Stinky
{
	//	model to draw model
	class Model
	{
	public:
		Model() 
		: primitiveType(0), drawCount(0), lineCount(0) {};

		DrawElementManager drawElementManager;	//	Has VAO, VBO, EBO

		unsigned int primitiveType;		//	how to draw 
		unsigned int drawCount;			//	how many draw
		unsigned int lineCount;			//	how many draw lines - In circle different line and drawing 
	};
}