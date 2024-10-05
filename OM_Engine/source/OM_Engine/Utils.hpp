#pragma once
#include <string>
#include <corecrt_math_defines.h>

namespace Utils
{
	const int SCREEN_WIDTH = 1280;
	const int SCREEN_HEIGHT = 720;
	const std::string APP_NAME = "OM_Engine";

	const float RAD_TO_DEG = 180.f / M_PI;
	const float DEG_TO_RAD = M_PI / 180.f;
	const float WEAK_ESPILON = 0.00001f;

	template<typename T>
	T Absolute(const T& value)
	{
		return value < 0 ? -value : value;
	}

	template<typename T>
	T Clamp(const T& value, const T min, const T max)
	{
		if (value < min)
			return min;
		else if (value > max)
			return max;
		else
			return value;
	}
}