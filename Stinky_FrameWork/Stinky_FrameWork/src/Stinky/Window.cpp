#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.hpp"
#include "GraphicEngine.hpp"
#include "Environment.hpp"

namespace Stinky
{
	extern int Width{};
	extern int Height{};

	static GLFWwindow* window;
	static int width;
	static int height;

	bool CreateWindow() noexcept
	{
		return CreateWindow("Stinky_Framework", 800, 600);
	}

	bool CreateWindow(const std::string& title) noexcept
	{
		return CreateWindow(title, 800, 600);
	}

	bool CreateWindow(int widths, int heights) noexcept
	{
		return CreateWindow("Stinky_Framework", widths, heights);
	}

	bool CreateWindow(const std::string& title, int widths, int heights) noexcept
	{
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // window dimensions are static
		//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		width = widths;
		height = heights;

		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		glViewport(0, 0, width, height);

		GraphicEngine& graphicEngine = GraphicEngine::Instance();
		graphicEngine.Init(static_cast<GLfloat>(width), static_cast<GLfloat>(height));

		Width = width;
		Height = height;

		return true;
	}

	void WindowClosing() noexcept
	{
		std::vector<Model>& models = GraphicEngine::GetModel();
		std::vector<Shader>& shaders = GraphicEngine::GetShader();
		std::map<std::string, Texture> images = GraphicEngine::GetImage();
		
		for (Model& model : models)
		{
			model.drawElementManager.DeleteAll();
		}

		for (Shader& shader : shaders)
		{
			shader.Delete();
		}

		for (auto& image : images)
		{
			image.second.Delete();
		}

		glfwDestroyWindow(window);
		window = NULL;

		glfwTerminate();
	}

	bool IsWindowClosed() noexcept
	{
		if (glfwWindowShouldClose(window))
		{
			WindowClosing();
			return true;
		}

		return false;
	}

	void UpdateWindow() noexcept
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		Camera& camera = GraphicEngine::GetCamera();
		camera.Update(static_cast<float>(width), static_cast<float>(height));

		glfwSwapBuffers(window);
		glfwPollEvents();

		std::stack<Option>& options = GraphicEngine::GetOptions();

		while (!options.empty())
		{
			options.pop();
		}

		PushSetting();

		Width = width;
		Height = height;
	}

	void CloseWindow() noexcept
	{
		glfwSetWindowShouldClose(window, true);
	}

	void SetWindowTitle(const std::string& title) noexcept
	{
		glfwSetWindowTitle(window, title.c_str());
	}

	void PushSetting()
	{
		GraphicEngine& engine = GraphicEngine::Instance();
		
		engine.PushSetting();
	}

	void PopSetting()
	{
		GraphicEngine& engine = GraphicEngine::Instance();

		engine.PopSetting();
	}

	void SetFrameReference(FrameReference frameReference)
	{
		Camera& cam = GraphicEngine::GetCamera();
		cam.SetFrameReference(frameReference);
	}

	void ClearBackground()
	{
		ClearBackground(Color{ 200, 200, 200, 255 });
	}

	void ClearBackground(Color color)
	{
		ColorNDC colors{ color };

		glClearColor(colors.red, colors.blue, colors.blue, colors.alpha);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void ClearBackground(HexColor color)
	{
		ClearBackground(Color{ color });
	}
}