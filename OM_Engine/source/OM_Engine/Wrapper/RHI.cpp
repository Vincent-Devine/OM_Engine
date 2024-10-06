#include "pch.h"

#include "OM_Engine/Wrapper/RHI.hpp"
#include "OM_Engine/Utils.hpp"
#include "OM_Engine/Wrapper/Window.hpp"
#include <Log_System/Log.hpp>

namespace Wrapper
{
	// Behavior
	bool RHI::Initialisation()
	{
		if (!Create_Instance())
			return false;
		return true;
	}

	void RHI::Update()
	{
		Load_Resource_In_RHI();
	}

	void RHI::Render() const
	{

	}

	void RHI::Destroy()
	{
		vkDestroyInstance(m_vulkan_instance, nullptr);
	}

	// Instance
	RHI* RHI::Get_Instance()
	{
		if (!s_instance)
			s_instance = new RHI();
		return s_instance;
	}

	// Vulkan
	bool RHI::Create_Instance()
	{
		VkApplicationInfo app_info{};
		app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		app_info.pApplicationName = Utils::APP_NAME.c_str();
		app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.pEngineName = Utils::APP_NAME.c_str();
		app_info.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		app_info.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo create_info{};
		create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		create_info.pApplicationInfo = &app_info;

		uint32_t glfw_extension_count = 0;
		const char** glfw_extensions;

		glfw_extensions = glfwGetRequiredInstanceExtensions(&glfw_extension_count);

		create_info.enabledExtensionCount = glfw_extension_count;
		create_info.ppEnabledExtensionNames = glfw_extensions;
		
		create_info.enabledLayerCount = 0;

		if (vkCreateInstance(&create_info, nullptr, &m_vulkan_instance) != VK_SUCCESS)
		{
			LOG_ERROR("Failed to create vulkan instance");
			return false;
		}
		return true;
	}

	// Load Resource
	void RHI::Load_Resource_In_RHI()
	{
		if (m_resources_to_load_in_rhi.size() == 0)
			return;

		while (m_resources_to_load_in_rhi.size() != 0)
		{
			if (m_mutex_resource_to_load_in_rhi.try_lock())
			{
				if (m_resources_to_load_in_rhi.empty())
				{
					m_mutex_resource_to_load_in_rhi.unlock();
					return;
				}

				m_resources_to_load_in_rhi.front()->Load_In_RHI();
				m_resources_to_load_in_rhi.pop();
				m_mutex_resource_to_load_in_rhi.unlock();
			}
		}
	}

	void RHI::Set_Resource_To_Load_In_RHI(Resource::iResource* resource)
	{
		if (m_mutex_resource_to_load_in_rhi.try_lock())
		{
			m_resources_to_load_in_rhi.push(resource);
			m_mutex_resource_to_load_in_rhi.unlock();
		}
	}
}