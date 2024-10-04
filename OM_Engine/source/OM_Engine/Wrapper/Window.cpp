#include "pch.h"

#include "OM_Engine/Wrapper/Window.hpp"
#include <Log_System/Log.hpp>
#include "OM_Engine/Utils.hpp"

namespace Wrapper
{
	// Behavior
	bool Window::Initialisation()
	{
		glfwSetErrorCallback(Display_Error);
		
		if (glfwInit() == GLFW_FALSE)
		{
			LOG_ERROR("GLFW could'nt initialited");
			return false;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_MAJOR_VERSION);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_MINOR_VERSION);

		m_window = glfwCreateWindow(Utils::SCREEN_WIDTH, Utils::SCREEN_HEIGHT, Utils::APP_NAME.c_str(), NULL, NULL);

		if (!m_window)
		{
			glfwTerminate();
			LOG_ERROR("GLFW could'nt create window");
			return false;
		}

		glfwMakeContextCurrent(m_window);
		glfwSetKeyCallback(m_window, On_Input);
		
		return true;
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::Render() const
	{
		glfwSwapBuffers(m_window);
	}

	void Window::Destroy()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		delete Get_Instance();
	}

	const bool Window::Window_Should_Close() const
	{
		bool closeWindow = glfwWindowShouldClose(m_window);
		if (closeWindow)
			LOG_INFO("Close window");

		return closeWindow;
	}

	// Instance
	Window* Window::Get_Instance()
	{
		if (!s_instance)
			s_instance = new Window();
		return s_instance;
	}

	// GLFW
	void Window::Display_Error(int error, const char* description)
	{
		LOG_ERROR("GLFW [" + std::to_string(error) + "] " + description);
	}

	void Window::On_Input(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == CLOSE_APP_KEY && action == CLOSE_APP_ACTION)
			glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

}