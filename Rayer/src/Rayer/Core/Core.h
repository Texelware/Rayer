#pragma once

#define BIT(x) (1 << x)

//////////////////////////////////////
///////////PLATFORMS/////////////////
////Windows => GLFWwindow(Using glfw)
////////////////////////////////////

#ifdef RAYER_PLATFORM_WINDOWS

	#define RAYER_WINDOW GLFWwindow

#endif