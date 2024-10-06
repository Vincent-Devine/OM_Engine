#include "pch.h"

#include "OM_Engine/Wrapper/Loader_Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <Log_System/Log.hpp>

namespace Wrapper
{
	unsigned char* Load_Texture(const std::string& path, int* witdh, int* height, int* channels)
	{
		unsigned char* data = stbi_load(path.c_str(), witdh, height, channels, 0);
		return data;
	}

	void Release_Texture(unsigned char* data)
	{
		stbi_image_free(data);
	}
}