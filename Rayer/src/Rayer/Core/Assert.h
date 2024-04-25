#pragma once

#include <iostream>
#include <Rayer/Core/Core.h>


//Rayer's core assert
#define RAYER_CORE_ASSERT(condition , message) { \
	if (!(condition)) {\
		 std::cerr << message << std::endl;\
		RAYER_DEBUG_BREAK; \
	}\
	}
