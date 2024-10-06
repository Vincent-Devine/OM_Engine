#pragma once

#include "OM_Engine/Base.hpp"

#include <vulkan/vulkan.h>
#include <queue>
#include <mutex>
#include "OM_Engine/Resource/iResource.hpp"

namespace Wrapper
{
	class OM_ENGINE_API RHI
	{
		// Behavior
	public:
		bool Initialisation();
		void Update();
		void Render() const;
		void Destroy();

		// Instance
	public:
		static RHI* Get_Instance();
	private:
		static inline RHI* s_instance = nullptr;

		// Vulkan
	private:
		VkInstance m_vulkan_instance;
		bool Create_Instance();

		// Load resource
	private:
		void Load_Resource_In_RHI();
		std::queue<Resource::iResource*> m_resources_to_load_in_rhi;
		std::mutex m_mutex_resource_to_load_in_rhi;

	public:
		void Set_Resource_To_Load_In_RHI(Resource::iResource* resource);

		// Getter and setter
	public:
		
	};
}