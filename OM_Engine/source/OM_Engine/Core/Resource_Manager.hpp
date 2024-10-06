#pragma once

#include "OM_Engine/Base.hpp"
#include <unordered_map>
#include <queue>
#include <mutex>
#include "OM_Engine/Resource/iResource.hpp"

namespace Core
{
	class OM_ENGINE_API Resource_Manager
	{
		// Behavior
	public:
		Resource::iResource* Use_Resource(const std::string& path, const Resource::RESOURCE_TYPE resource_type);
		void Stop_Used_Resource(Resource::iResource* resource);

	private:
		std::unordered_map<std::string, Resource::iResource*> m_resources;

		Resource::iResource* Get_Resource(const std::string& path);
		Resource::iResource* Create_Resource(const std::string& path, const Resource::RESOURCE_TYPE resource_type);
		void Add_Resource_To_Load(Resource::iResource* resource);
		void Delete_Resource(Resource::iResource* resource);

		// Instance
	public:
		static Resource_Manager* Get_Instance();
	private:
		static inline Resource_Manager* s_instance = nullptr;

		// Load resource
	public:
		Resource::iResource* Get_Resource_To_Load();
		
	private:
		std::mutex m_mutex_resource_to_load;
		std::queue<Resource::iResource*> m_resources_to_load;
	};
}