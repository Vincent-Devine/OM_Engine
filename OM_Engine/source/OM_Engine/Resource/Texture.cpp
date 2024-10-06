#include "pch.h"

#include "OM_Engine/Resource/Texture.hpp"
#include <Log_System/Log.hpp>
#include "OM_Engine/Wrapper/Loader_Texture.hpp"

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
		m_data = Wrapper::Load_Texture(m_path, &m_witdh, &m_height, &m_channels);
		if (!m_data)
		{
			LOG_WARNING("texture[" + std::to_string(m_id) + "] " + m_name + " failed to load");
			return false;
		}
		LOG_DEBUG("finish load texture: " + m_path);
		return true;
	}

	const bool Texture::Load_In_RHI()
	{
		// call rhi
		Wrapper::Release_Texture(m_data);
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