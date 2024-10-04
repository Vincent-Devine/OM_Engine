#include "pch.h"

#include "OM_Engine/Wrapper/RHI.hpp"

namespace Wrapper
{
	// Behavior


	// Instance
	RHI* RHI::Get_Instance()
	{
		if (!s_instance)
			s_instance = new RHI();
		return s_instance;
	}
}