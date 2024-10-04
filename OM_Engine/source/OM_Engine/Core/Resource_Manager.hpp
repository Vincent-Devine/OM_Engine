#pragma once

#include "OM_Engine/Base.hpp"
#include <unordered_map>
#include "OM_Engine/Resource/I_Resource.hpp"

namespace Core
{
	class OM_ENGINE_API Resource_Manager
	{
		// Behavior
	public:
		Resource::I_Resource* Use_Resource(const std::string& path, const Resource::RESOURCE_TYPE resource_type);
		void Stop_Used_Resource(Resource::I_Resource* resource);

	private:
		std::unordered_map<std::string, Resource::I_Resource*> m_resources;

		Resource::I_Resource* Get_Resource(const std::string& path);
		Resource::I_Resource* Create_Resource(const std::string& path, const Resource::RESOURCE_TYPE resource_type);
		void Load_Resource(Resource::I_Resource* resource);
		void Delete_Resource(Resource::I_Resource* resource);

		// Instance
	public:
		static Resource_Manager* Get_Instance();
	private:
		static inline Resource_Manager* s_instance = nullptr;
	};
}