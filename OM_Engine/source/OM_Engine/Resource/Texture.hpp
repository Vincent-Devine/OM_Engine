#pragma once

#include "OM_Engine/Base.hpp"
#include "OM_Engine/Resource/iResource.hpp"

namespace Resource
{
	class OM_ENGINE_API Texture : public iResource
	{
		// Behavior
	public:
		Texture(const int id, const std::string& path);
	
		const bool Load_From_File() override;
		const bool Load_In_RHI() override;

		void Draw(const unsigned int shader_program) const;

	private:
		int m_witdh, m_height, m_channels;
		unsigned char* m_data;
		unsigned int m_id_texture;
		std::string m_type;

		// Getter and setter
	public:
		const unsigned int Get_Id_Texture() const { return m_id_texture; }

		void Set_Path(const std::string& path) { m_path = path; }
		void Set_Id_Texture(const unsigned int id_texture) { m_id_texture = id_texture; }
		void Set_Type(const std::string& type) { m_type = type; }
	};
}