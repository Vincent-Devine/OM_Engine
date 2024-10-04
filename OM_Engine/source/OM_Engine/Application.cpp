#include "pch.h"
#include "OM_Engine/Application.hpp"

#include <Log_System/Log.hpp>

// Behavior
bool Application::Initialisation()
{
	Log::OpenFile("OM_Engine.log");

	m_window = Wrapper::Window::Get_Instance();
	if (!m_window->Initialisation())
		return false;

	LOG_INFO("initialisation complete");
	return true;
}

void Application::Update()
{
	m_window->Update();
}

void Application::Render() const
{
	m_window->Render();
}

void Application::Destroy()
{
	m_window->Destroy();
	LOG_INFO("destroy complete");
	Log::CloseFile();
}

const bool Application::Window_Should_Close() const
{
	return m_window->Window_Should_Close();
}
