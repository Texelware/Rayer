#pragma once
#include <Rayer/Utils/PlatformUtils.h>


namespace Rayer {

	class WindowsUtils : public PlatformUtils {

		public:

			virtual std::filesystem::path OpenFileDialog(const std::string filter) override;

	};

}