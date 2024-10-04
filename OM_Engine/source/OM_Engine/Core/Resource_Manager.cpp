#include "pch.h"

#include "OM_Engine/Core/Resource_Manager.hpp"
#include <Log_System/Log.hpp>
#include "OM_Engine/Resource/Texture.hpp"

namespace Core
{
	// Behavior
	Resource::I_Resource* Resource_Manager::Use_Resource(const std::string& path, const Resource::RESOURCE_TYPE resource_type)
	{
		Resource::I_Resource* resource = nullptr;
		resource = Get_Resource(path);

		if (!resource)
		{
			resource = Create_Resource(path, resource_type);
			Load_Resource(resource);
		}

		resource->Start_Using();
		return resource;
	}

	void Resource_Manager::Stop_Used_Resource(Resource::I_Resource* resource)
	{
		resource->Stop_Using();
		if (resource->Get_Used_By() == 0)
			Delete_Resource(resource);
	}

	Resource::I_Resource* Resource_Manager::Get_Resource(const std::string& path)
	{
		Resource::I_Resource* resource = nullptr;
		
		if (m_resources.count(path) != 0)
			resource = static_cast<Resource::I_Resource*>(m_resources.find(path)->second);
		
		return resource;
	}

	Resource::I_Resource* Resource_Manager::Create_Resource(const std::string& path, const Resource::RESOURCE_TYPE resource_type)
	{
		const unsigned int id = m_resources.size();
		Resource::I_Resource* resource = nullptr;

		switch (resource_type)
		{
		case Resource::RESOURCE_TYPE::texture:
			resource = static_cast<Resource::I_Resource*>(new Resource::Texture(id, path));
			break;

		default:
			break;
		}

		auto [it, _] = m_resources.insert_or_assign(path, resource);
		LOG_DEBUG("Add resource: " + path + " in resource manager!");
		return static_cast<Resource::I_Resource*>(it->second);
	}

	void Resource_Manager::Load_Resource(Resource::I_Resource* resource)
	{
		// call threadpool to load resoruce;
	}

	void Resource_Manager::Delete_Resource(Resource::I_Resource* resource)
	{
		resource->Unload();
		m_resources.erase(resource->Get_Path());
		LOG_DEBUG("Unload and delete resource: " + resource->Get_Name());
		delete resource;
	}

	Resource_Manager* Resource_Manager::Get_Instance()
	{
		if (!s_instance)
			s_instance = new Resource_Manager();
		return s_instance;
	}
}