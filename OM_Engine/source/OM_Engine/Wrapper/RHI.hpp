#pragma once

#include "OM_Engine/Base.hpp"

namespace Wrapper
{
	class OM_ENGINE_API RHI
	{
		// Behavior


		// Instance
	public:
		static RHI* Get_Instance();
	private:
		static inline RHI* s_instance = nullptr;

		// Getter and setter
	public:
		
	};
}