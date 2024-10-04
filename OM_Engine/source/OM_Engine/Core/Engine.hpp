#pragma once

#include "OM_Engine/Base.hpp"

namespace Core
{
	class OM_ENGINE_API Engine
	{
		// Behavior
	public:
		bool Initialisation();
		void Update();
		void Render();
		void Destroy();
	};
}