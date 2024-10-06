#pragma once
#include <string>

namespace Wrapper
{
	unsigned char* Load_Texture(const std::string& path, int* witdh, int* height, int* channels);
	void Release_Texture(unsigned char* data);
}