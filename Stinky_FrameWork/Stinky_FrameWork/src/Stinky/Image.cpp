#pragma once

#include <glad/glad.h>

#include <stb/stb_image.h>
#include "Image.hpp"
#include "Draw.hpp"
#include "Models.hpp"
#include "Shaders.hpp"
#include "Math/Matrix.hpp"
#include "GraphicEngine.hpp"

namespace Stinky
{
	//	function using only this cpp file
	std::map<std::string, Texture>::iterator AddingImage(std::string filepath);

	void AddImage(std::string filepath);

	Image::Image(std::string filepath)
	{
		textures = AddingImage(filepath);
	};

	void DrawImage(std::string filepath, float x, float y)
	{
		std::map<std::string, Texture>::iterator img = AddingImage(filepath);

		DrawImage(filepath, x, y, static_cast<GLfloat>(img->second.width), static_cast<float>(img->second.height), 0, 0,
			static_cast<float>(img->second.width), static_cast<float>(img->second.height));
	}

	void DrawImage(Image images, float x, float y)
	{
		DrawImage(images, x, y, static_cast<GLfloat>(images.textures->second.width), static_cast<float>(images.textures->second.height), 0, 0,
			static_cast<float>(images.textures->second.width), static_cast<float>(images.textures->second.height));
	}

	void DrawImage(std::string filepath, float x, float y, float width, float height)
	{
		std::map<std::string, Texture>::iterator img = AddingImage(filepath);

		DrawImage(filepath, x, y, width, height, 0, 0,
			static_cast<float>(img->second.width), static_cast<float>(img->second.height));
	}

	void DrawImage(Image images, float x, float y, float width, float height)
	{
		DrawImage(images, x, y, width, height, 0, 0,
			static_cast<float>(images.textures->second.width), static_cast<float>(images.textures->second.height));
	}

	void DrawImage(std::string filepath, float x, float y, float width, float height, float texel_x, float texel_y)
	{
		std::map<std::string, Texture>::iterator img = AddingImage(filepath);

		DrawImage(filepath, x, y, width, height,
			texel_x, texel_y, width, height);
	}

	void DrawImage(Image images, float x, float y, float width, float height, float texel_x, float texel_y)
	{
		DrawImage(images, x, y, width, height, texel_x, texel_y, width, height);
	}

	void DrawImage(std::string filepath, float x, float y, float width, float height,
		float texel_x, float texel_y, float texel_width, float texel_height)
	{
		DrawImage(Image{filepath}, x, y, width, height, texel_x, texel_y, texel_width, texel_height);
	}

	void DrawImage(Image images, float x, float y, float width, float height,
		float texel_x, float texel_y, float texel_width, float texel_height)
	{
		std::map<std::string, Texture>::iterator img = images.textures;

		GraphicEngine& engine = GraphicEngine::Instance();

		Model& model = engine.GetModel()[static_cast<unsigned int>(Models::texture)];
		Shader& shader = engine.GetShader()[static_cast<unsigned int>(Shaders::texture)];

		glm::vec4 tintColors{ engine.GetOptions().top().imageColors };

		shader.Activate();

		img->second.Active();

		//	draw except has alpha value
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		img->second.texUnit(shader, "texture0", GL_TEXTURE0);

		glm::vec2 texelPos = { texel_x / img->second.width, texel_y / img->second.height };
		shader.SetUniform("texelPos", texelPos.x, texelPos.y);

		glm::vec2 texelSize{ img->second.width / texel_width,img->second.height / texel_height };
		shader.SetUniform("texelSize", texelSize.x, texelSize.y);

		shader.SetUniform("noTint", engine.GetOptions().top().noTint);

		model.drawElementManager.VAOBind();

		shader.SetUniform_MToN_Matrix({ x, y }, { width, height });

		glVertexAttrib4f(2, tintColors.x, tintColors.y, tintColors.z, tintColors.w);
		glDrawElements(model.primitiveType, model.drawCount, GL_UNSIGNED_INT, NULL);

		model.drawElementManager.VAOUnBind();

		shader.UnActivate();
	}

	//	check map has image, if doesn't have add the image
	std::map<std::string, Texture>::iterator AddingImage(std::string filepath)
	{
		std::map<std::string, Texture>::iterator img = GraphicEngine::GetImage().find(filepath);

		if (img == GraphicEngine::GetImage().end())
		{
			AddImage(filepath);
		}

		return GraphicEngine::GetImage().find(filepath);
	}

	void AddImage(std::string filepath)
	{
		GraphicEngine::GetImage().insert(std::make_pair(filepath, Texture{}));

		std::map<std::string, Texture>::iterator texture = GraphicEngine::GetImage().find(filepath);

		texture->second.init(filepath.c_str(), GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE);
	}

	void SetTintColor(Color color)
	{
		ColorNDC col{ color };

		GraphicEngine::GetOptions().top().imageColors = {col.red, col.green, col.blue, col.alpha};
		GraphicEngine::GetOptions().top().noTint = false;
	}

	void NoTint()
	{
		GraphicEngine::GetOptions().top().noTint = true;
	}
}
