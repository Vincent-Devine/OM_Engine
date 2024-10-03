#pragma once

#include "OM_Engine/Base.hpp"
#include "OM_Engine/Wrapper/Window.hpp"

class OM_ENGINE_API Application
{
	// Behavior
public:
	bool Initialisation();
	void Update();
	void Render() const;
	void Destroy();

	// Window
public:
	const bool Window_should_close() const;
private:
	Wrapper::Window* m_window;
};