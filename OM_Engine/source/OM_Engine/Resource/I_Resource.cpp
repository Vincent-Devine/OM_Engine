#include "pch.h"

#include "OM_Engine/Resource/I_Resource.hpp"
#include <filesystem>

namespace Resource
{
	void I_Resource::Create_Name_From_File()
	{
		if (m_path == "")
			return;

		m_name = std::filesystem::path(m_path).filename().string();
	}
}