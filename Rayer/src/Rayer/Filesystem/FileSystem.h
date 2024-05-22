#pragma once
#include <iostream>
#include <filesystem>

namespace Rayer {

	namespace fs = std::filesystem;

	class RayerFileSystem {

	public:

		static std::string ReadFileToString(const std::string& path);
		static void CopyFileToDirectory(const fs::path& source, const fs::path& destination);

		static fs::path _currentWorkingPath;
	};

}