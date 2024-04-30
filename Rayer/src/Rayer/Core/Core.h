#pragma once

#include <memory>

#define BIT(x) (1 << x)


#ifdef RAYER_DEBUG
	#define RAYER_DEBUG_BREAK __debugbreak()
	
#else
	#define RAYER_DEBUG_BREAK
#endif
	

//////////////////////////////////////
///////////PLATFORMS/////////////////
////Windows => GLFWwindow(Using glfw)
////////////////////////////////////

#ifdef RAYER_PLATFORM_WINDOWS

	#define RAYER_WINDOW GLFWwindow

#endif

#define RAYER_BIND_EVENT_FN(x) std::bind(&x , this , std::placeholders::_1)

namespace Rayer {

	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using Scope = std::unique_ptr<T>;

	template <typename T , typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {

		return std::make_shared<T>(std::forward<Args>(args)...);

	}


	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args ... args) {

		return std::make_unique<T>(std::forward<Args>(args)...);
	}


}