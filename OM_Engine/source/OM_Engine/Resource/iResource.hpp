#pragma once

#include "OM_Engine/Base.hpp"
#include <string>

namespace Resource
{
	class OM_ENGINE_API iResource
	{
		// Behavior
	public:
		virtual ~iResource() {}
		virtual const bool Load_From_File() { return true; }
		virtual const bool Load_In_RHI() { return true; }
		virtual void Unload() {}

	protected:
		std::string m_path = "";
		std::string m_name = "";

		virtual void Create_Name_From_File();

		// Resource manager
	public:
		virtual void Start_Using() { m_used_by++; }
		virtual void Stop_Using() { m_used_by--; }

	protected:
		int m_id = -1;
		bool m_is_initialisate = false;
		unsigned int m_used_by = 0;

		// Getter and setter
	public:
		virtual const std::string& Get_Name() const { return m_name; }
		virtual const std::string& Get_Path() const { return m_path; }
		virtual const bool Get_Is_Initialisate() const { return m_is_initialisate; }
		virtual const unsigned int Get_Used_By() const { return m_used_by; }

		virtual void Set_Name(const std::string& name) { m_name = name; }
	};

	enum RESOURCE_TYPE
	{
		texture,
		mesh,
		vertex_shader,
		fragment_shader,
	};
}