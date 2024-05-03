
#include <Platform/Windows/WindowsWindow.h>

namespace Rayer {

	std::unique_ptr<IWindow> IWindow::Create(const WindowProperties& props) {

		//Platform  independent window creation
		#ifdef RAYER_PLATFORM_WINDOWS	
			return std::make_unique <WindowsWindow>(props);
		#endif

	}

}