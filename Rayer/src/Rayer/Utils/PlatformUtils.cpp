
#include <Rayer/Core/Assert.h>
#include "PlatformUtils.h"

#include <Platform/Windows/WindowsUtils.h>

namespace Rayer {

	Scope<PlatformUtils> PlatformUtils::Create() {

		#ifdef RAYER_PLATFORM_WINDOWS
			return CreateScope<WindowsUtils>();
		#endif 

		RAYER_CORE_ASSERT(false, "PLATFORM not supported !"); return nullptr;
	}

}