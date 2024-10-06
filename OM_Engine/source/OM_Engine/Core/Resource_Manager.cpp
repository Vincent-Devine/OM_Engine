#include "pch.h"

#include <Log_System/Log.hpp>
#include "OM_Engine/Core/Resource_Manager.hpp"
#include "OM_Engine/Core/Thread_Pool.hpp"
#include "OM_Engine/Wrapper/RHI.hpp"
#include "OM_Engine/Resource/Texture.hpp"

void Load_Resource()
{
	Resource::iResource* resource_to_load = Core::Resource_Manager::Get_Instance()->Get_Resource_To_Load();
	if (!resource_to_load)
		return;
	resource_to_load->Load_From_File();
	Wrapper::RHI::Get_Instance()->Set_Resource_To_Load_In_RHI(resource_to_load);
}

namespace Core
{
	// Behavior
	Resource::iResource* Resource_Manager::Use_Resource(const std::string& path, const Resource::RESOURCE_TYPE resource_type)
	{
		Resource::iResource* resource = nullptr;
		resource = Get_Resource(path);

		if (!resource)
		{
			resource = Create_Resource(path, resource_type);
			Add_Resource_To_Load(resource);
		}

		resource->Start_Using();
		return resource;
	}

	void Resource_Manager::Stop_Used_Resource(Resource::iResource* resource)
	{
		resource->Stop_Using();
		if (resource->Get_Used_By() == 0)
			Delete_Resource(resource);
	}

	Resource::iResource* Resource_Manager::Get_Resource(const std::string& path)
	{
		Resource::iResource* resource = nullptr;

		if (m_resources.count(path) != 0)
			resource = static_cast<Resource::iResource*>(m_resources.find(path)->second);

		return resource;
	}

	Resource::iResource* Resource_Manager::Create_Resource(const std::string& path, const Resource::RESOURCE_TYPE resource_type)
	{
		const unsigned int id = m_resources.size();
		Resource::iResource* resource = nullptr;

		switch (resource_type)
		{
		case Resource::RESOURCE_TYPE::texture:
			resource = static_cast<Resource::iResource*>(new Resource::Texture(id, path));
			break;

		default:
			break;
		}

		auto [it, _] = m_resources.insert_or_assign(path, resource);
		LOG_DEBUG("Add resource: " + path + " in resource manager!");
		return static_cast<Resource::iResource*>(it->second);
	}

	void Resource_Manager::Add_Resource_To_Load(Resource::iResource* resource)
	{
		if (m_mutex_resource_to_load.try_lock())
		{
			m_resources_to_load.push(resource);
			m_mutex_resource_to_load.unlock();
		}
		Core::Thread_Pool::Get_Instance()->Add_Task(Load_Resource);
	}

	void Resource_Manager::Delete_Resource(Resource::iResource* resource)
	{
		resource->Unload();
		m_resources.erase(resource->Get_Path());
		LOG_DEBUG("Unload and delete resource: " + resource->Get_Name());
		delete resource;
	}

	// Instance
	Resource_Manager* Resource_Manager::Get_Instance()
	{
		if (!s_instance)
			s_instance = new Resource_Manager();
		return s_instance;
	}

	// Load Resource
	Resource::iResource* Resource_Manager::Get_Resource_To_Load()
	{
		if (m_resources_to_load.empty())
			return nullptr;

		if (m_mutex_resource_to_load.try_lock())
		{
			if (m_resources_to_load.empty())
			{
				m_mutex_resource_to_load.unlock();
				return nullptr;
			}

			Resource::iResource* resource_to_load = m_resources_to_load.front();
			m_resources_to_load.pop();
			m_mutex_resource_to_load.unlock();
			return resource_to_load;
		}
		return nullptr;
	}
}