#pragma once

#include "OM_Engine/Base.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Wrapper
{
	class OM_ENGINE_API Window
	{
		// Instance
	public:
		static Window* Get_Instance();
	private:
		static inline Window* s_instance = nullptr;

		// Behavior
	public:
		bool Initialisation();
		void Update();
		void Render() const;
		void Destroy();
		
		const bool Window_Should_Close() const;

		// GLFW
	private:
		GLFWwindow* m_window;
		const unsigned int GLFW_MAJOR_VERSION = 4;
		const unsigned int GLFW_MINOR_VERSION = 5;
		static const int CLOSE_APP_KEY = GLFW_KEY_ESCAPE;
		static const int CLOSE_APP_ACTION = GLFW_PRESS;

		static void Display_Error(int error, const char* description);
		static void On_Input(GLFWwindow* window, int key, int scancode, int action, int mods);

	};
}