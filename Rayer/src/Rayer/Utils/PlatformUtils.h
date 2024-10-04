#pragma once
#include <Rayer/Core/Core.h>
#include <rpch.h>
#include <filesystem>

namespace Rayer {

	class PlatformUtils {

	public:

		virtual std::filesystem::path OpenFileDialog(const std::string filter) = 0;
		virtual std::filesystem::path SaveFile(const char* filter, const char* extension) = 0;

		static Scope<PlatformUtils> Create();

	};

}