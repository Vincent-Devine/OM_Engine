#include "pch.h"
#include <Log_System/Log.hpp>
#include "OM_Engine/Application.hpp"
#include "OM_Engine/Core/Thread_Pool.hpp"
#include "OM_Engine/Core/Resource_Manager.hpp"

// Behavior
bool Application::Initialisation()
{
	Log::OpenFile("OM_Engine.log");

	m_window = Wrapper::Window::Get_Instance();
	if (!m_window->Initialisation())
		return false;

	m_rhi = Wrapper::RHI::Get_Instance();
	if (!m_rhi->Initialisation())
		return false;

	Core::Thread_Pool::Get_Instance()->Initialisation();
	LOG_INFO("initialisation complete");

	Core::Resource_Manager::Get_Instance()->Use_Resource("assets/Texture/knaki.jpg", Resource::RESOURCE_TYPE::texture);

	return true;
}

void Application::Update()
{
	m_window->Update();
	m_rhi->Update();
}

void Application::Render() const
{
	m_window->Render();
	m_rhi->Render();
}

void Application::Destroy()
{
	m_rhi->Destroy();
	m_window->Destroy();
	Core::Thread_Pool::Get_Instance()->Destroy();
	LOG_INFO("destroy complete");
	Log::CloseFile();
}

const bool Application::Window_Should_Close() const
{
	return m_window->Window_Should_Close();
}
