#pragma once
#include <glad/glad.h>

#include "GraphicEngine.hpp"
#include "Math/Matrix.hpp"
#include "Color.hpp"

#include <array>
#include "Models.hpp"
#include "Shaders.hpp"

namespace Stinky
{
	//	inner function using only cpp file
	void DrawPlane(Models); //	draw only Plane
	void DrawLine(Models);	//	draw only line

	//	draw model - rectangle, ellipse
	void DrawModel(Models models, Shaders shaders, glm::vec2 translate, glm::vec2 scale)
	{
		GraphicEngine& engine = GraphicEngine::Instance();

		Model& mode = engine.GetModel()[static_cast<unsigned int>(models)];
		Shader& shader = engine.GetShader()[static_cast<unsigned int>(shaders)];
		
		shader.Activate();

		mode.drawElementManager.VAOBind();

		//	send model's vectors of translate and scale
		shader.SetUniform_MToN_Matrix(translate, scale);

		//	drawing
		DrawPlane(models);
		DrawLine(models);

		mode.drawElementManager.VAOUnBind();

		shader.UnActivate();
	}


	void DrawEllipse(float xPos, float yPos, float xSize, float ySize)
	{
		DrawModel(Models::ellipse, Shaders::instancing, {xPos, yPos}, {xSize / 2, ySize / 2});
	}

	void DrawEllipse(glm::vec2 v1, glm::vec2 v2)
	{
		DrawEllipse(v1.x, v1.y, v2.x, v2.y);
	}

	void DrawRect(float xPos, float yPos, float xSize, float ySize)
	{
		DrawModel(Models::rectangle, Shaders::instancing, { xPos, yPos }, { xSize, ySize });
	}

	void DrawRect(glm::vec2 v1, glm::vec2 v2)
	{
		DrawRect(v1.x, v1.y, v2.x, v2.y);
	}

	void SetFillColor(Color color)
	{
		GraphicEngine& engine = GraphicEngine::Instance();

		ColorNDC transformColor{ color };

		engine.GetOptions().top().noFill = false;
		engine.GetOptions().top().colors = { transformColor.red, transformColor.green, transformColor.blue, transformColor.alpha };
	}

	void SetFillColor(HexColor color)
	{
		SetFillColor(Color{ color });
	}

	void SetOutlineColor(Color color)
	{
		GraphicEngine& engine = GraphicEngine::Instance();

		ColorNDC transformColor{ color };

		engine.GetOptions().top().noOutLine = false;
		engine.GetOptions().top().outLineColors = { transformColor.red, transformColor.green, transformColor.blue, transformColor.alpha };
	}

	void SetOutlineColor(HexColor color)
	{
		SetOutlineColor(Color{ color });
	}

	void NoFill()
	{
		GraphicEngine::GetOptions().top().noFill = true;
	}

	void NoOutline()
	{
		GraphicEngine::GetOptions().top().noOutLine = true;
	}

	void SetOutlineWidth(float width)
	{
		GraphicEngine::GetOptions().top().outLine = width;
	}

	void DrawPlane(Models models)
	{
		GraphicEngine& engine = GraphicEngine::Instance();
		Model& model = engine.GetModel()[static_cast<unsigned int>(models)];

		glm::vec4 colors = engine.GetOptions().top().colors;

		//	no fill value is true doesn't draw
		if (engine.GetOptions().top().noFill == false)
		{
			glVertexAttrib4f(1, colors.x, colors.y, colors.z, colors.w);
			glDrawElements(model.primitiveType, model.drawCount, GL_UNSIGNED_INT, NULL);
		}
	}

	void DrawLine(Models models)
	{
		GraphicEngine& engine = GraphicEngine::Instance();
		Model& model = engine.GetModel()[static_cast<unsigned int>(models)];

		glm::vec4 colors = engine.GetOptions().top().outLineColors;

		glLineWidth(engine.GetOptions().top().outLine);
		//	no outline value is true doesn't draw
		if (engine.GetOptions().top().noOutLine == false)
		{
			glVertexAttrib4f(1, colors.x, colors.y, colors.z, colors.w);
			glDrawElements(GL_LINE_LOOP, model.lineCount, GL_UNSIGNED_INT, NULL);
		}
	}
}