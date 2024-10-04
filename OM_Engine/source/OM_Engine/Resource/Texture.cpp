#include "pch.h"

#include "OM_Engine/Resource/Texture.hpp"
#include <Log_System/Log.hpp>

namespace Resource
{
	// Behavior
	Texture::Texture(const int id, const std::string& path)
		: m_witdh(0), m_height(0), m_channels(0), m_data(), m_id_texture(0), m_type("")
	{
		m_path = path;
		m_name = "default_name_" + std::to_string(id);
		m_id = id;

		Create_Name_From_File();
	}

	const bool Texture::Load_From_File()
	{
		m_is_initialisate = false;
		// load from file (call wrapper)
		if (!m_data)
		{
			LOG_WARNING("texture[ " + std::to_string(m_id) + "] " + m_name + " failed to load");
			return false;
		}
		return true;
	}

	const bool Texture::Load_In_RHI()
	{
		// call rhi
		// release texture data
		m_is_initialisate = true;
		return true;
	}

	void Texture::Draw(const unsigned int shader_program) const
	{
		if (!m_is_initialisate)
			return;

		// call wrapper draw_texture
	}
}