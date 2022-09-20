#pragma once

#include "../Models/ModelElements.hpp"
#include "GraphicEngine.hpp"
#include "Math/Angle.hpp"
#include "Models.hpp"

#include <iostream>

namespace Stinky
{
	glm::mat3 identity{ 1, 0, 0, 0, 1, 0, 0, 0, 1 };

	GraphicEngine::GraphicEngine()
		:camera(Camera{}), matrix3{ identity } {	}

	//	inner function only using cpp file
	void DeclareShader();	//	saved shaders
	void DeclareModel();	//	saved models

	void GraphicEngine::Init(GLfloat width, GLfloat height)
	{
		DeclareShader();
		DeclareModel();

		PushSetting();	// initial push settings
		camera.Init(width, height);
	}

	void DeclareShader()
	{
		GraphicEngine::GetShader().clear();

		GraphicEngine::GetShader().push_back(Shader{ "src/Shaders/instancing.vert", "src/Shaders/instancing.frag" });
		GraphicEngine::GetShader().push_back(Shader{ "src/Shaders/texture.vert", "src/Shaders/texture.frag" });
	}

	//	saved each function different models
	void InstancingRect();
	void InstancingCircle(unsigned int counts);
	void InstancingTexture();

	void DeclareModel()
	{
		GraphicEngine::GetModel().clear();
		GraphicEngine::GetModel().resize(static_cast<unsigned int>(Models::counts));

		InstancingRect();
		InstancingCircle(50);
		InstancingTexture();
	}

	//	saved rectangle
	void InstancingRect()
	{
		float vertices[] =
		{
			 0.5f,  0.5f,  // top right
			 0.5f, -0.5f,  // bottom right
			-0.5f, -0.5f,  // bottom left
			-0.5f,  0.5f   // top left 
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 2, 3, 0
		};

		Model& model = GraphicEngine::GetModel()[static_cast<unsigned int>(Models::rectangle)];
		Stinky::DrawElementManager& drawElementManager = model.drawElementManager;

		drawElementManager.Add(new VAO);

		VBO* vbovert = new VBO{ vertices, sizeof(vertices) };

		drawElementManager.Add(vbovert);

		drawElementManager.Add(new EBO{ indices, sizeof(indices) });

		drawElementManager.VAOLinkAttrib(vbovert, 0, 2, GL_FLOAT, 0, (void*)0);

		drawElementManager.UnBindAll();

		model.primitiveType = GL_TRIANGLE_STRIP;
		model.drawCount = static_cast<GLuint>(sizeof(indices) / sizeof(unsigned int));
		model.lineCount = model.drawCount;
	}

	//	saved circle's model - nums can make different numbers of vertices
	//	numbers of vertices can determine inner graphicEngine instance
	void InstancingCircle(unsigned int nums)
	{	
		int lineNums = nums + 1;
		int indicesNum = (nums + 2);
		int verticesNum = indicesNum * 2;

		float* vertices = new float[verticesNum];
		unsigned int* indices = new unsigned int[indicesNum];
		unsigned int* lineIndices = new unsigned int[lineNums];

		unsigned int verticesIndex = 0;
		unsigned int index = 0;

		*(vertices + verticesIndex) = 0.f;
		verticesIndex++;
		*(vertices + verticesIndex) = 0.f;
		verticesIndex++;
		*(indices + index) = index;

		index++;

		float angle = 0.f;
		float radians = TWO_PI / static_cast<float>(nums);

		float radious = 1.5f;	//	to make diameter == 1.f

		while (angle < TWO_PI)	//	included lineIndices
		{
			*(vertices + verticesIndex) = static_cast<float>(std::cos(angle) * radious);
			verticesIndex++;
			*(vertices + verticesIndex) = static_cast<float>(std::sin(angle) * radious);
			verticesIndex++;

			*(indices + index) = index;
			*(lineIndices + index - 1) = index;
				
			angle += radians;
			index++;
		}

		*(vertices + verticesIndex) = static_cast<float>(std::cos(0) * radious);	//	x_position
		verticesIndex++;
		*(vertices + verticesIndex) = static_cast<float>(std::sin(0) * radious);	//	y_position

		*(indices + index) = 1;
		*(lineIndices + index - 1) = 1;

		Model& model = GraphicEngine::GetModel()[static_cast<unsigned int>(Models::ellipse)];
		Stinky::DrawElementManager& drawElementManager = model.drawElementManager;

		drawElementManager.Add(new VAO);

		VBO* vbovert = new VBO{ vertices, static_cast<int>(sizeof(float) * verticesNum) };

		drawElementManager.Add(vbovert);

		drawElementManager.Add(new EBO{ indices, static_cast<int>(sizeof(unsigned int) * indicesNum) });
		drawElementManager.Add(new EBO{ lineIndices, static_cast<int>(sizeof(unsigned int) * lineNums) });

		drawElementManager.VAOLinkAttrib(vbovert, 0, 2, GL_FLOAT, 0, (void*)0);

		drawElementManager.UnBindAll();

		model.primitiveType = GL_TRIANGLE_FAN;
		model.drawCount = indicesNum;
		model.lineCount = lineNums;

		delete[] vertices;
		delete[] indices;
		delete[] lineIndices;
	}

	//	saved texture's model
	void InstancingTexture()
	{
		float vertices[] =
		{
			 0.5f,  0.5f,  // top right
			 0.5f, -0.5f,  // bottom right
			-0.5f, -0.5f,  // bottom left
			-0.5f,  0.5f   // top left 
		};

		float texCoord[]
		{
			1.f, 1.f,  // top right
			1.f, 0.f,  // bottom right
			0.f, 0.f,  // bottom left
			0.f, 1.f,   // top left 
		};

		unsigned int indices[] = {  // note that we start from 0!
			0, 1, 2, 3, 0
		};

		Model& model = GraphicEngine::GetModel()[static_cast<unsigned int>(Models::texture)];
		Stinky::DrawElementManager& drawElementManager = model.drawElementManager;

		drawElementManager.Add(new VAO);

		VBO* vbovert = new VBO{ vertices, sizeof(vertices) };
		VBO* vbotex = new VBO{ texCoord, sizeof(texCoord) };

		drawElementManager.Add(vbovert);

		drawElementManager.Add(new EBO{ indices, sizeof(indices) });

		drawElementManager.VAOLinkAttrib(vbovert, 0, 2, GL_FLOAT, 0, (void*)0);
		drawElementManager.VAOLinkAttrib(vbotex, 1, 2, GL_FLOAT, 0, (void*)0);

		drawElementManager.UnBindAll();

		model.primitiveType = GL_TRIANGLE_STRIP;
		model.drawCount = static_cast<GLuint>(sizeof(indices) / sizeof(unsigned int));
		model.lineCount = model.drawCount;
	}

	//	push option value
	void GraphicEngine::PushSetting()
	{
		if (!options.empty())
		{
			options.push(options.top());
		}
		else
		{
			options.push(Option{});
		}
	}

	//	pop option value
	void GraphicEngine::PopSetting()
	{
		if (options.size() > 1)
		{
			matrix3 *= options.top().popMatrix3s;

			options.pop();
		}
	}

	Option::Option()
		:popMatrix3s(identity), outLineColors({ 0.f, 0.f, 0.f, 0.f }), colors({ 1.f, 1.f, 1.f, 1.f }), imageColors({ 1.f, 1.f, 1.f, 1.f }), noTint(true), noFill(false), noOutLine(false), outLine(5.f) {	}
}